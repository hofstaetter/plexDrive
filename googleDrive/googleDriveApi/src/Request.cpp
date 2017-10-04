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
    this->queryStrings = queryString;
    this->headers = header;
    this->postFields = postFields;
    this->body = body;
}

size_t Request::writeBuffer(char *ptr, size_t size, size_t nmemb, void *stream)
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
    for(auto p : this->queryStrings) {
        url.append((url.find("?") == string::npos) ? "?" : "&").append(p.first.c_str()).append("=").append(p.second.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


    //set postFields
    string postfields;
    if(type.compare("POST") == 0) {
        for(auto p : this->postFields) {
            postfields.append((postfields.empty()) ? "" : "&").append(p.first).append("=").append(p.second.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postfields.length());
    }


    //set headers
    struct curl_slist *headerList=NULL;
    headerList = curl_slist_append(headerList, ("Host: " + host.substr(host.find("://", 0) + 3, host.length() - host.find("://", 0))).c_str());
    headerList = curl_slist_append(headerList, ("Content-length: " + to_string(body.length() + postfields.length())).c_str());
    headerList = curl_slist_append(headerList, "Connection: close");
    headerList = curl_slist_append(headerList, "User-Agent: plexDrive");
    for(auto p : this->headers) {
        headerList = curl_slist_append(headerList, (p.first + ": " + p.second).c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

    //write response to buffer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &result.header);

    cout << "[VERBOSE] " << this->type << " " << url << endl;

    CURLcode curlResult = curl_easy_perform(curl);

    cout << "[VERBOSE] " << result.header.substr(0, result.header.find("\n") - 1) << endl; // " " << result.body << endl;

    if(curlResult != CURLE_OK && curlResult != CURLE_RECV_ERROR) {
        cout << "[ERROR] " << "Request failed..." << endl;
        throw exception();
    }

    //cleanup
    curl_easy_cleanup(curl);

    //get http status code
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result.httpStatusCode);
    return result;
}

void Request::addQueryString(string key, string value) {
    this->queryStrings.insert(make_pair(key, value));
}

void Request::addHeader(string key, string value) {
    this->headers.insert(make_pair(key, value));
}

void Request::addPostField(string key, string value) {
    this->postFields.insert(make_pair(key, value));
}

void Request::setBody(string body) {
    this->body = body;
}
