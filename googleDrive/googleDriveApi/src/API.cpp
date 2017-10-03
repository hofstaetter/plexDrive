//
// Created by Matthias Hofstätter on 11.09.17.
//

#include <iostream>
#include "API.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

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

string bodyBuffer = "";
string headerBuffer = "";

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
API::request(string host, string path, string type, map<string, string> queryString, map<string, string> header, map<string, string> postFields, string body, string& responseHeaders, string& responseBody) {
    CURL *curl = curl_easy_init();

    //build & set url
    string url;

    url.append(host);
    url.append(path);
    for(auto &p : queryString) {
        url.append((url.find("?") == string::npos) ? "?" : "&").append(p.first.c_str()).append("=").append(p.second.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


    //set postFields
    string postfields;
    if(type.compare("POST") == 0) {
        for(auto &p : postFields) {
            postfields.append((postfields.empty()) ? "" : "&").append(p.first).append("=").append(p.second.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postfields.length());
    }


    //set headers
    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, ("Host: " + host.substr(host.find("://", 0) + 3, host.length() - host.find("://", 0))).c_str());
    headers = curl_slist_append(headers, ("Content-length: " + to_string(body.length() + postfields.length())).c_str());
    headers = curl_slist_append(headers, "Connection: close");
    headers = curl_slist_append(headers, "User-Agent: plexDrive");
    for(auto &p : header) {
        headers = curl_slist_append(headers, (p.first + ": " + p.second).c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //write response to buffer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBodyBuffer);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeHeaderBuffer);

    cout << "[VERBOSE] " << type << " " << url << endl;

    CURLcode result = curl_easy_perform(curl);

    cout << "[VERBOSE] " << headerBuffer.substr(0, headerBuffer.find("\n") - 1) << endl; // " " << bodyBuffer << endl;

    long statuscode;
    if(result == CURLE_OK || result == CURLE_RECV_ERROR) { //TODO MACOSX FIX
        //cleanup
        curl_easy_cleanup(curl);

        responseHeaders = headerBuffer;
        responseBody = bodyBuffer;

        bodyBuffer.clear();
        headerBuffer.clear();

        //get http status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statuscode);
        return statuscode;
    }

    //retry
    //if(statuscode == 500) return request(host, path, type, queryString, header, postFields, body, responseHeaders, responseBody);

    throw -1;
}

long
API::request(string host, string path, string type, map<string, string> queryString, map<string, string> header, map<string, string> postFields, string body, string& responseHeaders, FILE *file) {
    CURL *curl = curl_easy_init();

    //build & set url
    string url;

    url.append(host);
    url.append(path);
    for(auto &p : queryString) {
        url.append((url.find("?") == string::npos) ? "?" : "&").append(p.first.c_str()).append("=").append(p.second.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


    //set postFields
    string postfields;
    if(type.compare("POST") == 0) {
        for(auto &p : postFields) {
            postfields.append((postfields.empty()) ? "" : "&").append(p.first).append("=").append(p.second.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postfields.length());
    }


    //set headers
    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, ("Host: " + host.substr(host.find("://", 0) + 3, host.length() - host.find("://", 0))).c_str());
    headers = curl_slist_append(headers, ("Content-length: " + to_string(body.length() + postfields.length())).c_str());
    headers = curl_slist_append(headers, "Connection: close");
    headers = curl_slist_append(headers, "User-Agent: plexDrive");
    for(auto &p : header) {
        headers = curl_slist_append(headers, (p.first + ": " + p.second).c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //write response to buffer
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeHeaderBuffer);

    cout << "[VERBOSE] " << type << " " << url << endl;

    //perform
    CURLcode result = curl_easy_perform(curl);

    cout << "[VERBOSE] " << headerBuffer.substr(0, headerBuffer.find("\n") - 1) << endl;

    long statuscode;
    if(result == CURLE_OK || result == CURLE_RECV_ERROR) { //TODO MACOSX FIX
        //cleanup
        curl_easy_cleanup(curl);

        responseHeaders = headerBuffer;

        headerBuffer.clear();

        //get http status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statuscode);
        return statuscode;
    }

    throw -1;
}

void API::prepare(CURL *curl, string host, string path, string type, map<string, string> queryString,
                  map<string, string> header, map<string, string> postFields, string body) {
    //timeout
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);


    //build & set url
    string url;

    url.append(host);
    url.append(path);
    for(auto &p : queryString) {
        url.append((url.find("?") == string::npos) ? "?" : "&").append(p.first.c_str()).append("=").append(p.second.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


    //set postFields
    string postfields;
    if(type.compare("POST") == 0) {
        for(auto &p : postFields) {
            postfields.append((postfields.empty()) ? "" : "&").append(p.first).append("=").append(p.second.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postfields.length());
    }


    //set headers
    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, ("Host: " + host.substr(host.find("://", 0) + 3, host.length() - host.find("://", 0))).c_str());
    headers = curl_slist_append(headers, ("Content-length: " + to_string(body.length() + postfields.length())).c_str());
    headers = curl_slist_append(headers, "Connection: close");
    headers = curl_slist_append(headers, "User-Agent: plexDrive");
    for(auto &p : header) {
        headers = curl_slist_append(headers, (p.first + ": " + p.second).c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

}

long API::execute(CURL *curl) {
    //perform
    CURLcode result = curl_easy_perform(curl);

    long statuscode;
    if(result == CURLE_OK || result == CURLE_RECV_ERROR) { //TODO MACOSX FIX
        //cleanup
        curl_easy_cleanup(curl);

        //get http status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statuscode);
        return statuscode;
    }
    throw -1;
}
