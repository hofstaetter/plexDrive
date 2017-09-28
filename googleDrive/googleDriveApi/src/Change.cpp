//
// Created by Matthias Hofstätter on 14.09.17.
//

#include "changes/Change.h"
#include "files/File.h"
#include "teamdrives/TeamDrive.h"

Change::Change() {
    //this->document = new rapidjson::Document;
}

Change::Change(rapidjson::Document &document) {
    /*this->document = new rapidjson::Document;
    this->document->CopyFrom(document, (this->document)->GetAllocator());*/
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("type"))
        this->type = document["type"].GetString();
    if(document.HasMember("datetime"))
        this->datetime = time(NULL);
    if(document.HasMember("removed"))
        this->removed = document["removed"].GetBool();
    if(document.HasMember("fileId"))
        this->fileId = document["fileId"].GetString();
    if(document.HasMember("file")) {
        rapidjson::Document d(rapidjson::kObjectType);
        d.CopyFrom(document["file"], d.GetAllocator());
        this->file = File::File(d);
    }
    if(document.HasMember("teamDriveId"))
        this->teamDriveId = document["teamDriveId"].GetString();
    if(document.HasMember("teamDrive")) {
        rapidjson::Document document(rapidjson::kObjectType);
        document.CopyFrom(document["teamDrive"], document.GetAllocator());
        this->teamDrive = TeamDrive::TeamDrive(document);
    }

}

string &Change::getKind() {
    return kind;
}

void Change::setKind(string &kind) {
    this->kind = kind;
}

string &Change::getType() {
    return type;
}

void Change::setType(string &type) {
    this->type = type;
}

time_t Change::getDatetime() {
    return datetime;
}

void Change::setDatetime(time_t datetime) {
    this->datetime = datetime;
}

bool Change::isRemoved() {
    return removed;
}

void Change::setRemoved(bool removed) {
    this->removed = removed;
}

string &Change::getFileId() {
    return fileId;
}

void Change::setFileId(string &fileId) {
    this->fileId = fileId;
}

class File &Change::getFile() {
    return file;
}

void Change::setFile(class File file) {
    this->file = file;
}

string &Change::getTeamDriveId() {
    return teamDriveId;
}

void Change::setTeamDriveId(string &teamDriveId) {
    this->teamDriveId = teamDriveId;
}

class TeamDrive &Change::getTeamDrive() {
    return teamDrive;
}

void Change::setTeamDrive(class TeamDrive teamDrive) {
    this->teamDrive = teamDrive;
}

/*string Change::getKind() {
    return this->getString("kind");
}

void Change::setKind(string kind) {
    this->setString("kind", kind);
}

string Change::getType() {
    return this->getString("type");
}

void Change::setType(string type) {
    this->setString("type", type);
}

time_t Change::getDatetime() {
    return 0; //TODO
}

void Change::setDatetime(time_t datetime) {
    //TODO
}

bool Change::isRemoved() {
    return this->getBool("removed");
}

void Change::setRemoved(bool removed) {
    this->setBool("removed", removed);
}

string Change::getFileId() {
    return this->getString("fileId");
}

void Change::setFileId(string fileId) {
    this->setString("fileId", fileId);
}

File Change::getFile() {
    return this->getObject<File>("File");
}

void Change::setFile(File File) {
    this->setObject<class File>("File", File);
}

string Change::getTeamDriveId() {
    return this->getString("teamDriveId");
}

void Change::setTeamDriveId(string teamDriveId) {
    this->setString("teamDriveId", teamDriveId);
}

class TeamDrive Change::getTeamDrive() {
    return this->getObject<class TeamDrive>("TeamDrive");
}

void Change::setTeamDrive(class TeamDrive TeamDrive) {
    this->setObject<class TeamDrive>("TeamDrive", TeamDrive);
}*/
