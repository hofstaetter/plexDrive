//
// Created by Matthias Hofstätter on 21.08.17.
//

#include "files/GeneratedIds.h"

GeneratedIds::GeneratedIds() {

}

GeneratedIds::GeneratedIds(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("space"))
        this->space = document["space"].GetString();
    if(document.HasMember("ids"))
        for(auto& v : document["ids"].GetArray()) {
            this->ids.push_back(v.GetString());
        }
}

string &GeneratedIds::getKind() {
    return kind;
}

void GeneratedIds::setKind(string &kind) {
    GeneratedIds::kind = kind;
}

string &GeneratedIds::getSpace() {
    return space;
}

void GeneratedIds::setSpace(string &space) {
    GeneratedIds::space = space;
}

vector<string> &GeneratedIds::getIds() {
    return ids;
}

void GeneratedIds::setIds(vector<string> &ids) {
    GeneratedIds::ids = ids;
}
