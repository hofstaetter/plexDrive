//
// Created by Matthias Hofstätter on 14.09.17.
//

#include "changes/StartPageToken.h"

StartPageToken::StartPageToken() {

}

StartPageToken::StartPageToken(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("startPageToken"))
        this->startPageToken = document["startPageToken"].GetString();
}

string &StartPageToken::getKind() {
    return kind;
}

void StartPageToken::setKind(string &kind) {
    StartPageToken::kind = kind;
}

string &StartPageToken::getStartPageToken() {
    return startPageToken;
}

void StartPageToken::setStartPageToken(string &startPageToken) {
    StartPageToken::startPageToken = startPageToken;
}
