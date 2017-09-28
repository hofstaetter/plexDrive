//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "comments/Comment.h"

Comment::Comment() {

}

Comment::Comment(rapidjson::Document &document) {
    throw -2;
}

string &Comment::getKind() {
    return kind;
}

void Comment::setKind(string &kind) {
    Comment::kind = kind;
}

string &Comment::getId() {
    return id;
}

void Comment::setId(string &id) {
    Comment::id = id;
}

time_t Comment::getCreatedTime() {
    return createdTime;
}

void Comment::setCreatedTime(time_t createdTime) {
    Comment::createdTime = createdTime;
}

time_t Comment::getModifiedTime() {
    return modifiedTime;
}

void Comment::setModifiedTime(time_t modifiedTime) {
    Comment::modifiedTime = modifiedTime;
}

User &Comment::getAuthor() {
    return author;
}

void Comment::setAuthor(User &author) {
    Comment::author = author;
}

string &Comment::getHtmlContent() {
    return htmlContent;
}

void Comment::setHtmlContent(string &htmlContent) {
    Comment::htmlContent = htmlContent;
}

string &Comment::getContent() {
    return content;
}

void Comment::setContent(string &content) {
    Comment::content = content;
}

bool Comment::isDeleted() {
    return deleted;
}

void Comment::setDeleted(bool deleted) {
    Comment::deleted = deleted;
}

bool Comment::isResolved() {
    return resolved;
}

void Comment::setResolved(bool resolved) {
    Comment::resolved = resolved;
}
