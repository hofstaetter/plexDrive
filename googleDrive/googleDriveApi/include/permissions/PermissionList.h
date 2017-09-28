//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_PERMISSIONSLISTRESPONSE_H
#define PLEXDRIVE_PERMISSIONSLISTRESPONSE_H

#include <string>
#include <vector>
#include <permissions/Permission.h>
#include <document.h>

using namespace std;

class PermissionList {
private:
    string kind;
    string nextPageToken;
    vector<Permission> permissions;
public:
    PermissionList();
    PermissionList(rapidjson::Document &document);

    string &getKind();

    void setKind(string &kind);

    string &getNextPageToken();

    void setNextPageToken(string &nextPageToken);

    vector<Permission> &getPermissions();

    void setPermissions(vector<Permission> &permissions);
};


#endif //PLEXDRIVE_PERMISSIONSLISTRESPONSE_H
