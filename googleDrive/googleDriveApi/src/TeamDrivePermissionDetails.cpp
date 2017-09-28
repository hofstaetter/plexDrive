//
// Created by Matthias Hofstätter on 22.09.17.
//

#include "permissions/TeamDrivePermissionDetails.h"

TeamDrivePermissionDetails::TeamDrivePermissionDetails() {

}

TeamDrivePermissionDetails::TeamDrivePermissionDetails(rapidjson::Document &document) {
    throw -1;
}

string &TeamDrivePermissionDetails::getTeamDrivePermissionType() {
    return teamDrivePermissionType;
}

void TeamDrivePermissionDetails::setTeamDrivePermissionType(string &teamDrivePermissionType) {
    TeamDrivePermissionDetails::teamDrivePermissionType = teamDrivePermissionType;
}

string &TeamDrivePermissionDetails::getRole() {
    return role;
}

void TeamDrivePermissionDetails::setRole(string &role) {
    TeamDrivePermissionDetails::role = role;
}

string &TeamDrivePermissionDetails::getInheritedFrom() {
    return inheritedFrom;
}

void TeamDrivePermissionDetails::setInheritedFrom(string &inheritedFrom) {
    TeamDrivePermissionDetails::inheritedFrom = inheritedFrom;
}

bool TeamDrivePermissionDetails::isInherited() {
    return inherited;
}

void TeamDrivePermissionDetails::setInherited(bool inherited) {
    TeamDrivePermissionDetails::inherited = inherited;
}
