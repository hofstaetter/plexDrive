//
// Created by Matthias Hofstätter on 21.08.17.
//

#ifndef GOOGLEDRIVEAPI_USER_H
#define GOOGLEDRIVEAPI_USER_H

#include <string>
#include "document.h"

using namespace std;

class User {
private:
    string kind;
    string displayName;
    string photoLink;
    bool me;
    string permissionId;
    string emailAddress;
public:
    User();
    User(rapidjson::Document &document);

    string &toString();
    rapidjson::Document &toJSON();
    
    string &getKind();
    void setKind(string &kind);

    string &getDisplayName();
    void setDisplayName(string &displayName);

    string &getPhotoLink();
    void setPhotoLink(string &photoLink);

    bool isMe();
    void setMe(bool me);

    string &getPermissionId();
    void setPermissionId(string &permissionId);

    string &getEmailAddress();
    void setEmailAddress(string &emailAddress);
};


#endif //GOOGLEDRIVEAPI_USER_H
