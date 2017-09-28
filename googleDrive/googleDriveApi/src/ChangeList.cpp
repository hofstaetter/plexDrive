//
// Created by Matthias Hofstätter on 14.09.17.
//

#include "changes/ChangeList.h"

ChangeList::ChangeList() {
}

ChangeList::ChangeList(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("nextPageToken"))
        this->nextPageToken = document["nextPageToken"].GetString();
    if(document.HasMember("newStartPageToken"))
        this->newStartPageToken = document["newStartPageToken"].GetString();
    if(document.HasMember("changes")) {
        rapidjson::Document d(rapidjson::kObjectType);
        for(auto &c : document["changes"].GetArray()) {
            d.CopyFrom(c, d.GetAllocator());
            this->changes.push_back(Change(d));
        }
    }
}

string &ChangeList::getKind() {
    return kind;
}

void ChangeList::setKind(string &kind) {
    ChangeList::kind = kind;
}

string &ChangeList::getNextPageToken() {
    return nextPageToken;
}

void ChangeList::setNextPageToken(string &nextPageToken) {
    ChangeList::nextPageToken = nextPageToken;
}

string &ChangeList::getNewStartPageToken() {
    return newStartPageToken;
}

void ChangeList::setNewStartPageToken(string &newStartPageToken) {
    ChangeList::newStartPageToken = newStartPageToken;
}

vector<Change> &ChangeList::getChanges() {
    return changes;
}

void ChangeList::setChanges(vector<Change> &changes) {
    ChangeList::changes = changes;
}
