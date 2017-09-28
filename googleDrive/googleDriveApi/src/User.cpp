//
// Created by Matthias Hofstätter on 21.08.17.
//

#include <User.h>
#include <stringbuffer.h>
#include <writer.h>

User::User() {

}

User::User(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("displayName"))
        this->displayName = document["displayName"].GetString();
    if(document.HasMember("photoLink"))
        this->photoLink = document["photoLink"].GetString();
    if(document.HasMember("me"))
        this->me = document["me"].GetBool();
    if(document.HasMember("permissionId"))
        this->permissionId = document["permissionId"].GetString();
    if(document.HasMember("emailAddress"))
        this->emailAddress = document["emailAddress"].GetString();
}

string &User::getKind() {
    return kind;
}

void User::setKind(string &kind) {
    User::kind = kind;
}

string &User::getDisplayName() {
    return displayName;
}

void User::setDisplayName(string &displayName) {
    User::displayName = displayName;
}

string &User::getPhotoLink() {
    return photoLink;
}

void User::setPhotoLink(string &photoLink) {
    User::photoLink = photoLink;
}

bool User::isMe() {
    return me;
}

void User::setMe(bool me) {
    User::me = me;
}

string &User::getPermissionId() {
    return permissionId;
}

void User::setPermissionId(string &permissionId) {
    User::permissionId = permissionId;
}

string &User::getEmailAddress() {
    return emailAddress;
}

void User::setEmailAddress(string &emailAddress) {
    User::emailAddress = emailAddress;
}

string &User::toString() {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    this->toJSON().Accept(writer);

    string result(buffer.GetString());
    return result;
}

rapidjson::Document &User::toJSON() {
    rapidjson::Document d(rapidjson::kObjectType);

    d.AddMember(rapidjson::StringRef("kind"), rapidjson::StringRef(this->kind.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("displayName"), rapidjson::StringRef(this->displayName.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("photoLink"), rapidjson::StringRef(this->photoLink.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("me"), rapidjson::Value(me), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("permissionId"), rapidjson::StringRef(this->permissionId.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("emailAddress"), rapidjson::StringRef(this->emailAddress.c_str()), d.GetAllocator());

    return d;
}
