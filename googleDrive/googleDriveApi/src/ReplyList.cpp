//
// Created by Matthias Hofstätter on 17.09.17.
//

#include "replies/ReplyList.h"

ReplyList::ReplyList() {

}

ReplyList::ReplyList(rapidjson::Document &document) {
    throw -1;
}

string &ReplyList::getKind() {
    return kind;
}

void ReplyList::setKind(string &kind) {
    ReplyList::kind = kind;
}

string &ReplyList::getNextPageToken() {
    return nextPageToken;
}

void ReplyList::setNextPageToken(string &nextPageToken) {
    ReplyList::nextPageToken = nextPageToken;
}

vector<Reply> &ReplyList::getReplies() {
    return replies;
}

void ReplyList::setReplies(vector<Reply> &replies) {
    ReplyList::replies = replies;
}
