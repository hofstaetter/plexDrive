//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_TEAMDRIVES_H
#define PLEXDRIVE_TEAMDRIVES_H


#include <teamdrives/TeamDrive.h>
#include <teamdrives/TeamDriveList.h>

class Teamdrives {
public:
    static TeamDrive create(string requestId, TeamDrive requestBody,
                            bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static void del(string teamDriveId,
                    bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static TeamDrive get(string teamDriveId,
                         bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static TeamDriveList list(int pageSize = 10, string pageToken = "",
                              bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static TeamDrive update(string teamDriveId, TeamDrive requestBody,
                            bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
};


#endif //PLEXDRIVE_TEAMDRIVES_H
