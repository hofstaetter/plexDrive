//
// Created by Matthias Hofstätter on 18.09.17.
//

#include "teamdrives/TeamDriveList.h"


TeamDriveList::TeamDriveList() {

}

TeamDriveList::TeamDriveList(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("nextPageToken"))
        this->nextPageToken = document["nextPageToken"].GetString();
    if(document.HasMember("teamDrives")) {
        for(rapidjson::Value::ConstMemberIterator itr = document["teamDrives"].MemberBegin(); itr == document["teamDrives"].MemberEnd(); itr++) {
            rapidjson::Document d;
            d.CopyFrom(itr->value, d.GetAllocator());
            this->teamDrives.emplace_back(TeamDrive(d));
        }
    }
}

string &TeamDriveList::getKind() {
    return this->kind;
}

void TeamDriveList::setKind(string &kind) {
    this->kind = kind;
}

string &TeamDriveList::getNextPageToken() {
    return this->nextPageToken;
}

void TeamDriveList::setNextPageToken(string &nextPageToken) {
    this->nextPageToken = nextPageToken;
}

vector<TeamDrive> &TeamDriveList::getTeamDrives() {
    return this->teamDrives;
}

void TeamDriveList::setTeamDrives(vector<TeamDrive> &teamDrives) {
    this->teamDrives = teamDrives;
}
