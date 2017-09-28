//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_TEAMDRIVELIST_H
#define PLEXDRIVE_TEAMDRIVELIST_H


#include <teamdrives/TeamDrive.h>
#include <string>
#include <vector>

using namespace std;

class TeamDriveList {
private:
    string kind;
    string nextPageToken;
    vector<TeamDrive> teamDrives;
public:
    TeamDriveList();
    TeamDriveList(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getNextPageToken();
    void setNextPageToken(string &nextPageToken);

    vector<TeamDrive> &getTeamDrives();
    void setTeamDrives(vector<TeamDrive> &teamDrives);
};


#endif //PLEXDRIVE_TEAMDRIVELIST_H
