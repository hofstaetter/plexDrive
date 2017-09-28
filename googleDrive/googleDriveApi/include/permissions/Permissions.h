//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_PERMISSIONSGOOGLEDRIVEAPI_H
#define PLEXDRIVE_PERMISSIONSGOOGLEDRIVEAPI_H


#include "permissions/Permission.h"
#include "permissions/PermissionList.h"

class Permissions {
public:
    static Permission create(string fileId, string emailMessage = "", bool sendNotificationEmail = false, bool suportsTeamDrives = false, bool transferOwnership = false, Permission requestBody = {},
                                      bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static void del(string fileId, string permissionId, bool supportsTeamDrives = false,
                    bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Permission get(string fileId, string permissionId, bool supportsTeamDrives = false,
                                   bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static PermissionList list(string fileId, int pageSize = 100, string pageToken = "", bool supportsTeamDrives = false,
                                        bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Permission update(string fileId, string permissionId, bool removeExpiration = false, bool supportsTeamDrives = false, bool transferOwnership = false,
                                      bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
};


#endif //PLEXDRIVE_PERMISSIONSGOOGLEDRIVEAPI_H
