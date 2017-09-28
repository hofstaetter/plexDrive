//
// Created by Matthias Hofstätter on 21.08.17.
//

#ifndef GOOGLEDRIVEAPI_WATCHRESPONSE_H
#define GOOGLEDRIVEAPI_WATCHRESPONSE_H


#include "files/Files.h"
#include <string>
#include <map>

using namespace std;

class Channel {
private:
    string kind;
    string id;
    string resourceId;
    string resourceUri;
    string token;
    long expiration;
    string type;
    string address;
    bool payload;
    map<string, string> params;
public:
    Channel();
    Channel(rapidjson::Document& document);

    string &getKind();
    void setKind(string &kind);

    string &getId();
    void setId(string &id);

    string &getResourceId();
    void setResourceId(string &resourceId);

    string &getResourceUri();
    void setResourceUri(string &resourceUri);

    string &getToken();
    void setToken(string &token);

    long getExpiration();
    void setExpiration(long expiration);

    string &getType();
    void setType(string &type);

    string &getAddress();
    void setAddress(string &address);

    bool isPayload();
    void setPayload(bool payload);

    map<string, string> &getParams();
    void setParams(map<string, string> &params);
};


#endif //GOOGLEDRIVEAPI_WATCHRESPONSE_H
