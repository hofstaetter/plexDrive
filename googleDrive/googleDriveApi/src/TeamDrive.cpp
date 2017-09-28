//
// Created by Matthias Hofstätter on 14.09.17.
//

#include "teamdrives/TeamDrive.h"

TeamDrive::TeamDrive() {
}

TeamDrive::TeamDrive(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("name"))
        this->name = document["name"].GetString();
    if(document.HasMember("themeId"))
        this->themeId = document["themeId"].GetString();
    if(document.HasMember("colorRgb"))
        this->colorRgb = document["colorRgb"].GetString();
    if(document.HasMember("BackgroundImageFile")) {
        rapidjson::Document d(rapidjson::kObjectType);
        d.CopyFrom(document["BackgroundImageFile"], d.GetAllocator());
        this->backgroundImageFile = BackgroundImageFile::BackgroundImageFile(d);
    }
    if(document.HasMember("backgroundImageLink"))
        this->backgroundImageLink = document["backgroundImageLink"].GetString();
    if(document.HasMember("Capabilities")) {
        rapidjson::Document d(rapidjson::kObjectType);
        d.CopyFrom(document["Capabilities"], d.GetAllocator());
        this->capabilities = Capabilities(d);
    }
}

/*string TeamDrive::getKind() {
    return this->getString("kind");
}

void TeamDrive::setKind(string kind) {
    this->setString("kind", kind);
}

string TeamDrive::getName() {
    return this->getString("name");
}

void TeamDrive::setName(string name) {
    this->setString("name", name);
}

string TeamDrive::getThemeId() {
    return this->getString("themeId");
}

void TeamDrive::setThemeId(string themeId) {
    this->setString("themeId", themeId);
}

string TeamDrive::getColorRgb() {
    return this->getString("colorRgb");
}

void TeamDrive::setColorRgb(string colorRgb) {
    this->setString("colorRgb", colorRgb);
}

BackgroundImageFile TeamDrive::getBackgroundImageFile() {
    return this->getObject<class BackgroundImageFile>("BackgroundImageFile");
}

void TeamDrive::setBackgroundImageFile(BackgroundImageFile BackgroundImageFile) {
    this->setObject<class BackgroundImageFile>("BackgroundImageFile", BackgroundImageFile);
}

string TeamDrive::getBackgroundImageLink() {
    return this->getString("backgroundImageLink");
}

void TeamDrive::setBackgroundImageLink(string backgroundImageLink) {
    this->setString("backgroundImageLink", backgroundImageLink);
}

Capabilities TeamDrive::getCapabilities() {
    return this->getObject<class Capabilities>("Capabilities");
}

void TeamDrive::setCapabilities(Capabilities Capabilities) {
}*/


string &TeamDrive::getKind() {
    return kind;
}

void TeamDrive::setKind(string &kind) {
    TeamDrive::kind = kind;
}

string &TeamDrive::getName() {
    return name;
}

void TeamDrive::setName(string &name) {
    TeamDrive::name = name;
}

string &TeamDrive::getThemeId() {
    return themeId;
}

void TeamDrive::setThemeId(string &themeId) {
    TeamDrive::themeId = themeId;
}

string &TeamDrive::getColorRgb() {
    return colorRgb;
}

void TeamDrive::setColorRgb(string &colorRgb) {
    TeamDrive::colorRgb = colorRgb;
}

class BackgroundImageFile &TeamDrive::getBackgroundImageFile() {
    return backgroundImageFile;
}

void TeamDrive::setBackgroundImageFile(class BackgroundImageFile &backgroundImageFile) {
    TeamDrive::backgroundImageFile = backgroundImageFile;
}

string &TeamDrive::getBackgroundImageLink() {
    return backgroundImageLink;
}

void TeamDrive::setBackgroundImageLink(string &backgroundImageLink) {
    TeamDrive::backgroundImageLink = backgroundImageLink;
}

class Capabilities &TeamDrive::getCapabilities() {
    return capabilities;
}

void TeamDrive::setCapabilities(class Capabilities &capabilities) {
    TeamDrive::capabilities = capabilities;
}
