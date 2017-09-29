//
// Created by Matthias Hofstätter on 11.09.17.
//

#ifndef GOOGLEDRIVEAPI_HTTPS_H
#define GOOGLEDRIVEAPI_HTTPS_H

#include <curl/curl.h>
#include <string>
#include <map>
#include <rapidjson.h>
#include <document.h>
#include <iostream>

using namespace std;

class API {
public:
    static long request(string host, string path, string type, map<string, string> queryString, map<string, string> header, map<string, string> postFields, string body, string &responseHeaders, string &responseBody);
};


#endif //GOOGLEDRIVEAPI_HTTPS_H
