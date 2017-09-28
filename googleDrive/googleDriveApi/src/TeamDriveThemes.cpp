//
// Created by Matthias Hofstätter on 19.09.17.
//

#include "about/TeamDriveThemes.h"

TeamDriveThemes::TeamDriveThemes() {

}

TeamDriveThemes::TeamDriveThemes(rapidjson::Document &document) {
    throw -2;
}

string &TeamDriveThemes::getId() {
    return id;
}

void TeamDriveThemes::setId(string &id) {
    TeamDriveThemes::id = id;
}

string &TeamDriveThemes::getBackgroundImageLink() {
    return backgroundImageLink;
}

void TeamDriveThemes::setBackgroundImageLink(string &backgroundImageLink) {
    TeamDriveThemes::backgroundImageLink = backgroundImageLink;
}

string &TeamDriveThemes::getColorRgb() {
    return colorRgb;
}

void TeamDriveThemes::setColorRgb(string &colorRgb) {
    TeamDriveThemes::colorRgb = colorRgb;
}
