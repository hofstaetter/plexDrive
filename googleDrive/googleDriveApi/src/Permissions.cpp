//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "permissions/Permissions.h"

Permission Permissions::create(string fileId, string emailMessage, bool sendNotificationEmail,
                                                      bool suportsTeamDrives, bool transferOwnership,
                                                      Permission requestBody, bool alt, string fields,
                                                      bool prettyPrint, string quotaUser, string userId) {
    return Permission();
}

void
Permissions::del(string fileId, string permissionId, bool supportsTeamDrives, bool alt, string fields,
                               bool prettyPrint, string quotaUser, string userId) {

}

Permission
Permissions::get(string fileId, string permissionId, bool supportsTeamDrives, bool alt, string fields,
                               bool prettyPrint, string quotaUser, string userId) {
    return Permission();
}

PermissionList
Permissions::list(string fileId, int pageSize, string pageToken, bool supportsTeamDrives, bool alt,
                                string fields, bool prettyPrint, string quotaUser, string userId) {
    return PermissionList();
}

Permission
Permissions::update(string fileId, string permissionId, bool removeExpiration, bool supportsTeamDrives,
                                  bool transferOwnership, bool alt, string fields, bool prettyPrint, string quotaUser,
                                  string userId) {
    return Permission();
}
