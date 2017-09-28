//
// Created by Matthias Hofstätter on 22.09.17.
//

#ifndef PLEXDRIVE_TEAMDRIVEPERMISSIONDETAILS_H
#define PLEXDRIVE_TEAMDRIVEPERMISSIONDETAILS_H

#include <document.h>
#include <string>

using namespace std;

class TeamDrivePermissionDetails {
private:
    string teamDrivePermissionType;
    string role;
    string inheritedFrom;
    bool inherited;
public:
    TeamDrivePermissionDetails();
    TeamDrivePermissionDetails(rapidjson::Document &document);

    string &getTeamDrivePermissionType();
    void setTeamDrivePermissionType(string &teamDrivePermissionType);

    string &getRole();
    void setRole(string &role);

    string &getInheritedFrom();
    void setInheritedFrom(string &inheritedFrom);

    bool isInherited();
    void setInherited(bool inherited);

};


#endif //PLEXDRIVE_TEAMDRIVEPERMISSIONDETAILS_H
