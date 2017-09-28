//
// Created by Matthias Hofstätter on 18.09.17.
//

#include "revisions/RevisionList.h"

RevisionList::RevisionList() {}

RevisionList::RevisionList(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("nextPageToken"))
        this->nextPageToken = document["nextPageToken"].GetString();
    if(document.HasMember("Revisions"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("Revisions")) {
        for(rapidjson::Value::ConstMemberIterator itr = document["Revisions"].MemberBegin(); itr == document["Revisions"].MemberEnd(); itr++) {
            rapidjson::Document d;
            d.CopyFrom(itr->value, d.GetAllocator());
            this->revisions.emplace_back(Revision(d));
        }
    }
}

string &RevisionList::getKind() {
    return kind;
}

void RevisionList::setKind(string &kind) {
    RevisionList::kind = kind;
}

string &RevisionList::getNextPageToken() {
    return nextPageToken;
}

void RevisionList::setNextPageToken(string &nextPageToken) {
    RevisionList::nextPageToken = nextPageToken;
}

vector<Revision> &RevisionList::getRevisions() {
    return revisions;
}

void RevisionList::setRevisions(vector<Revision> &revisions) {
    RevisionList::revisions = revisions;
}
