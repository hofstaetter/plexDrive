//
// Created by Matthias Hofstätter on 14.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVEAPICHANGES_H
#define PLEXDRIVE_GOOGLEDRIVEAPICHANGES_H


#include "StartPageToken.h"
#include "ChangeList.h"
#include "channels/Channel.h"

class ChangesApi {
public:
    static StartPageToken getStartPageToken(bool supportsTeamDrives = false, string teamDriveId = "",
                                            string alt = "", std::string fields = "", bool prettyPrint = true, std::string quotaUser = "", std::string userId = "");
    static ChangeList list(string pageToken, bool includeCorpusRemovals = false, bool includeRemoved = true, bool includeTeamDriveItems = false, int pageSize = 100, bool restrictToMyDrive = false, string spaces = "", bool supportsTeamDrives = false,
                                    string teamDriveId = "",
                                    string alt = "", std::string fields = "", bool prettyPrint = true, std::string quotaUser = "", std::string userId = "");
    static Channel watch(string pageToken, bool includeCorpusRemovals = false, bool includeRemoved = true, bool includeTeamDriveItems = false, int pageSize = 100, bool restrictToMyDrive = false, string spaces = "", bool supportsTeamDrives = false,
                                      string teamDriveId = "", Channel requestBody = {},
                                      string alt = "", std::string fields = "", bool prettyPrint = true, std::string quotaUser = "", std::string userId = "");
};


#endif //PLEXDRIVE_GOOGLEDRIVEAPICHANGES_H
