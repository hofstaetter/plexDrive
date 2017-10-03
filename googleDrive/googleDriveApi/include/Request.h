//
// Created by Matthias Hofstätter on 01.10.17.
//

#ifndef PLEXDRIVE_REQUEST_H
#define PLEXDRIVE_REQUEST_H

#include <string>
#include <map>
#include "Response.h"

using namespace std;

class Request {
private:
    string host;
    string path;
    string type;
    map<string, string> queryString;
    map<string, string> header;
    map<string, string> postFields;
    string body;

public:
    Request();
    Request(string host, string path, string type, map<string, string> queryString, map<string, string> header, map<string, string> postFields, string body);

    Response execute();

    void addQueryString(string key, string value);
    void addHeader(string key, string value);
    void addPostField(string key, string value);
};


#endif //PLEXDRIVE_REQUEST_H
