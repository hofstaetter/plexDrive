//
// Created by Matthias Hofstätter on 11.09.17.
//

#include <iostream>
#include "API.h"
#include <chrono>

using namespace std;

static
void dump(const char *text,
          FILE *stream, unsigned char *ptr, size_t size)
{
    size_t i;
    size_t c;
    unsigned int width=0x10;

    fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n",
            text, (long)size, (long)size);

    for(i=0; i<size; i+= width) {
        fprintf(stream, "%4.4lx: ", (long)i);

        /* show hex to the left */
        for(c = 0; c < width; c++) {
            if(i+c < size)
                fprintf(stream, "%02x ", ptr[i+c]);
            else
                fputs("   ", stream);
        }

        /* show data on the right */
        for(c = 0; (c < width) && (i+c < size); c++) {
            char x = (ptr[i+c] >= 0x20 && ptr[i+c] < 0x80) ? ptr[i+c] : '.';
            fputc(x, stream);
        }

        fputc('\n', stream); /* newline */
    }
}

static
int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
    const char *text;
    (void)handle; /* prevent compiler warning */
    (void)userp;

    switch (type) {
        case CURLINFO_TEXT:
            fprintf(stderr, "== Info: %s", data);
        default: /* in case a new one is introduced to shock us */
            return 0;

        case CURLINFO_HEADER_OUT:
            text = "=> Send header";
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data";
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data";
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header";
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data";
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data";
            break;
    }

    dump(text, stderr, (unsigned char *)data, size);
    return 0;
}

string bodyBuffer;
string headerBuffer;

size_t
writeBodyBuffer(char *ptr, size_t size, size_t nmemb, void *stream)
{
    bodyBuffer.append(ptr, size*nmemb);
    return size*nmemb;
}

size_t
writeHeaderBuffer(char *ptr, size_t size, size_t nmemb, void *stream)
{
    headerBuffer.append(ptr, size*nmemb);
    return size*nmemb;
}

long
API::request(string host, string path, string type, map<string, string> querystring, map<string, string> header, map<string, string> postfields, string body, string& responseHeaders, string& responseBody) {
    //chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    CURL *req = curl_easy_init();

    curl_global_init(CURL_GLOBAL_ALL);

    curl_easy_setopt(req, CURLOPT_DEBUGFUNCTION, my_trace);

    curl_version_info_data *d = curl_version_info(CURLVERSION_NOW);

    //debug
    curl_easy_setopt(req, CURLOPT_VERBOSE, 1L);

    //build & set url
    string url;
    bool first = true;

    url.append(host); //url static
    url.append(path);
    for(auto &p : querystring) {
        if(p.second.compare("") == 0) continue;
        if(first) {
            url.append("?");
            first = false;
        } else url.append("&");
        url.append(curl_easy_escape(req, p.first.c_str(), p.first.length())).append("=").append(curl_easy_escape(req, p.second.c_str(), p.second.length()));
        //url.append(p.first.c_str()).append("=").append(p.second.c_str());
    }
    curl_easy_setopt(req, CURLOPT_URL, url.c_str());

    curl_easy_setopt(req, CURLOPT_SSL_VERIFYHOST, 0L);

    long contentlength = 0;

    //set postfields
    string pf = "";
    if(type.compare("POST") == 0) {
        first = true;
        for(auto p : postfields) {
            if(!first) {
                pf.append("&");
            }
            pf.append(p.first);
            pf.append("=");
            pf.append(p.second.c_str());
            first = false;
        }
        curl_easy_setopt(req, CURLOPT_POSTFIELDS, pf.c_str());
        curl_easy_setopt(req, CURLOPT_POSTFIELDSIZE, pf.length());
        contentlength += pf.length();
    }

    //write response to buffer
    curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, writeBodyBuffer);
    curl_easy_setopt(req, CURLOPT_HEADERFUNCTION, writeHeaderBuffer);

    //set headers
    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, ("Host: " + host.substr(host.find("://", 0) + 3, host.length() - host.find("://", 0))).c_str());

    contentlength += body.length();
    headers = curl_slist_append(headers, ("Content-length: " + to_string(contentlength)).c_str());
    headers = curl_slist_append(headers, "Connection: close");
    for(auto p : header) {
        headers = curl_slist_append(headers, (p.first + ": " + p.second).c_str());
    }
    curl_easy_setopt(req, CURLOPT_HTTPHEADER, headers);

    //chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::milliseconds ms =chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch());
    cout << ms.count() << " [REQUEST] "  << type << " " << url << endl << pf << endl << body << endl;

    CURLcode result = curl_easy_perform(req);

    //chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

    long statuscode;
    if(result == CURLE_OK || result == CURLE_RECV_ERROR) {
        //get http status code
        curl_easy_getinfo(req, CURLINFO_RESPONSE_CODE, &statuscode);

        responseBody = bodyBuffer;

        responseHeaders = headerBuffer;
        cout << ms.count() << " [RESPONSE] "  << type << " " << host << path << endl << responseBody << endl;
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);

    curl_easy_cleanup(req);

    //debug
    //cout << bodyBuffer << endl;

    bodyBuffer.clear();
    headerBuffer.clear();

    //retry
    if(statuscode == 500) return request(host, path, type, querystring, header, postfields, body, responseHeaders, responseBody);

    //chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();

    //chrono::duration<double, milli> d1 = t2 - t1;
    //chrono::duration<double, milli> d2 = t3 - t2;
    //chrono::duration<double, milli> d3 = t4 - t3;

    //cout << "[HTTPSREQUEST] Prepare: " << d1.count() << " ms | Execute: " << d2.count() << " ms | Finish: " << d3.count() << " ms" << endl;

    return statuscode;
}
