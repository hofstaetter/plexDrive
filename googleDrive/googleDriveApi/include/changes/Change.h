//
// Created by Matthias Hofstätter on 14.09.17.
//

#ifndef PLEXDRIVE_CHANGES_H
#define PLEXDRIVE_CHANGES_H


#include <ctime>
#include <string>
#include "files/File.h"
#include "teamdrives/TeamDrive.h"

using namespace std;

class Change {
private:
    string kind;
    string type;
    time_t datetime;
    bool removed;
    string fileId;
    class File file;
    string teamDriveId;
    class TeamDrive teamDrive;
public:
    Change();
    Change(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getType();
    void setType(string &type);

    time_t getDatetime();
    void setDatetime(time_t datetime);

    bool isRemoved();
    void setRemoved(bool removed);

    string &getFileId();
    void setFileId(string &fileId);

    class File &getFile();
    void setFile(class File file);

    string &getTeamDriveId();
    void setTeamDriveId(string &teamDriveId);

    class TeamDrive &getTeamDrive();
    void setTeamDrive(class TeamDrive teamDrive);
};


#endif //PLEXDRIVE_CHANGES_H
