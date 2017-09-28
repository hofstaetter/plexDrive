//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "permissions/PermissionList.h"

PermissionList::PermissionList() {

}

PermissionList::PermissionList(rapidjson::Document &document) {
    throw -1;
}

string &PermissionList::getKind() {
    return kind;
}

void PermissionList::setKind(string &kind) {
    PermissionList::kind = kind;
}

string &PermissionList::getNextPageToken() {
    return nextPageToken;
}

void PermissionList::setNextPageToken(string &nextPageToken) {
    PermissionList::nextPageToken = nextPageToken;
}

vector<Permission> &PermissionList::getPermissions() {
    return permissions;
}

void PermissionList::setPermissions(vector<Permission> &permissions) {
    PermissionList::permissions = permissions;
}
