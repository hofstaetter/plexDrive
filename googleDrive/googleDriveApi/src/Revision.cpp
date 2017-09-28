//
// Created by Matthias Hofstätter on 18.09.17.
//

#include "revisions/Revision.h"

Revision::Revision() {

}

Revision::Revision(rapidjson::Document &document) {

}

string &Revision::getKind() {
    return kind;
}

void Revision::setKind(string &kind) {
    Revision::kind = kind;
}

string &Revision::getId() {
    return id;
}

void Revision::setId(string &id) {
    Revision::id = id;
}

string &Revision::getMimeType() {
    return mimeType;
}

void Revision::setMimeType(string &mimeType) {
    Revision::mimeType = mimeType;
}

string &Revision::getModifiedTime() {
    return modifiedTime;
}

void Revision::setModifiedTime(string &modifiedTime) {
    Revision::modifiedTime = modifiedTime;
}

bool Revision::isKeepForever() {
    return keepForever;
}

void Revision::setKeepForever(bool keepForever) {
    Revision::keepForever = keepForever;
}

bool Revision::isPublishAuto() {
    return publishAuto;
}

void Revision::setPublishAuto(bool publishAuto) {
    Revision::publishAuto = publishAuto;
}

bool Revision::isPublishedOutsideDomain() {
    return publishedOutsideDomain;
}

void Revision::setPublishedOutsideDomain(bool publishedOutsideDomain) {
    Revision::publishedOutsideDomain = publishedOutsideDomain;
}

User &Revision::getLastModifyingUser() {
    return lastModifyingUser;
}

void Revision::setLastModifyingUser(User &lastModifyingUser) {
    Revision::lastModifyingUser = lastModifyingUser;
}

string &Revision::getOriginalFilename() {
    return originalFilename;
}

void Revision::setOriginalFilename(string &originalFilename) {
    Revision::originalFilename = originalFilename;
}

string &Revision::getMd5Checksum() {
    return md5Checksum;
}

void Revision::setMd5Checksum(string &md5Checksum) {
    Revision::md5Checksum = md5Checksum;
}

long Revision::getSize() {
    return size;
}

void Revision::setSize(long size) {
    Revision::size = size;
}
