//
// Created by Matthias Hofstätter on 17.09.17.
//

#include "replies/Reply.h"

Reply::Reply() {

}

Reply::Reply(rapidjson::Document &document) {
    throw -1;
}

string &Reply::getKind() {
    return kind;
}

void Reply::setKind(string &kind) {
    Reply::kind = kind;
}

string &Reply::getId() {
    return id;
}

void Reply::setId(string &id) {
    Reply::id = id;
}

time_t Reply::getCreatedTime() {
    return createdTime;
}

void Reply::setCreatedTime(time_t createdTime) {
    Reply::createdTime = createdTime;
}

time_t Reply::getModifiedTime() {
    return modifiedTime;
}

void Reply::setModifiedTime(time_t modifiedTime) {
    Reply::modifiedTime = modifiedTime;
}

User &Reply::getAuthor() {
    return author;
}

void Reply::setAuthor(User &author) {
    Reply::author = author;
}

string &Reply::getHtmlContent() {
    return htmlContent;
}

void Reply::setHtmlContent(string &htmlContent) {
    Reply::htmlContent = htmlContent;
}

string &Reply::getContent() {
    return content;
}

void Reply::setContent(string &content) {
    Reply::content = content;
}

bool Reply::isDeleted() {
    return deleted;
}

void Reply::setDeleted(bool deleted) {
    Reply::deleted = deleted;
}

string &Reply::getAction() {
    return action;
}

void Reply::setAction(string &action) {
    Reply::action = action;
}
