//
// Created by Matthias Hofstätter on 01.10.17.
//

#include "Request.h"
#include <curl/curl.h>
#include <stdio.h>
#include <iostream>

Request::Request() {

}

Request::Request(string host, string path, string type, map<string, string> queryString, map<string, string> header,
                 map<string, string> postFields, string body) {
    this->host = host;
    this->path = path;
    this->type = type;
    this->queryString = queryString;
    this->header = header;
    this->postFields = postFields;
    this->body = body;
}

size_t writeBuffer(char *ptr, size_t size, size_t nmemb, void *stream)
{
    ((string *)stream)->append(ptr, size*nmemb);
    return size*nmemb;
}

Response Request::execute() {
    Response result;

    CURL *curl = curl_easy_init();
    //build & set url
    string url;

    url.append(this->host);
    url.append(this->path);
    for(auto &p : this->queryString) {
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &result.header);

    cout << "[VERBOSE] " << this->type << " " << url << endl;

    CURLcode curlResult = curl_easy_perform(curl);

    cout << "[VERBOSE] " << result.header.substr(0, result.header.find("\n") - 1) << endl; // " " << result.body << endl;

    if(curlResult == CURLE_OK || curlResult == CURLE_RECV_ERROR) { //TODO MACOSX FIX
        //cleanup
        curl_easy_cleanup(curl);

        //get http status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result.httpStatusCode);
        return result;
    }

    //retry
    //if(statuscode == 500) return request(host, path, type, queryString, header, postFields, body, responseHeaders, responseBody);

    throw -1;
}
