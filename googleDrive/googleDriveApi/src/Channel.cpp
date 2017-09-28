//
// Created by Matthias Hofstätter on 21.08.17.
//

#include "channels/Channel.h"

Channel::Channel() {}

Channel::Channel(rapidjson::Document& document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("id"))
        this->id = document["id"].GetString();
    if(document.HasMember("resourceId"))
        this->resourceId = document["resourceId"].GetString();
    if(document.HasMember("resourceUri"))
        this->resourceUri = document["resourceUri"].GetString();
    if(document.HasMember("token"))
        this->token = document["token"].GetString();
    if(document.HasMember("expiration"))
        this->expiration = document["expiration"].GetInt64();
    if(document.HasMember("type"))
        this->type = document["type"].GetString();
    if(document.HasMember("address"))
        this->address = document["address"].GetString();
    if(document.HasMember("payload"))
        this->payload = document["payload"].GetBool();
    if(document.HasMember("params")) {
        for(auto& v : document["params"].GetArray()) {
            this->params.insert(pair<string, string>(v[0].GetString(), v[1].GetString()));
        }
    }
}

string &Channel::getKind() {
    return kind;
}

void Channel::setKind(string &kind) {
    Channel::kind = kind;
}

string &Channel::getId() {
    return id;
}

void Channel::setId(string &id) {
    Channel::id = id;
}

string &Channel::getResourceId() {
    return resourceId;
}

void Channel::setResourceId(string &resourceId) {
    Channel::resourceId = resourceId;
}

string &Channel::getResourceUri() {
    return resourceUri;
}

void Channel::setResourceUri(string &resourceUri) {
    Channel::resourceUri = resourceUri;
}

string &Channel::getToken() {
    return token;
}

void Channel::setToken(string &token) {
    Channel::token = token;
}

long Channel::getExpiration() {
    return expiration;
}

void Channel::setExpiration(long expiration) {
    Channel::expiration = expiration;
}

string &Channel::getType() {
    return type;
}

void Channel::setType(string &type) {
    Channel::type = type;
}

string &Channel::getAddress() {
    return address;
}

void Channel::setAddress(string &address) {
    Channel::address = address;
}

bool Channel::isPayload() {
    return payload;
}

void Channel::setPayload(bool payload) {
    Channel::payload = payload;
}

map<string, string> &Channel::getParams() {
    return params;
}

void Channel::setParams(map<string, string> &params) {
    Channel::params = params;
}



