//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "comments/CommentList.h"

CommentList::CommentList() {

}

CommentList::CommentList(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("nextPageToken"))
        this->nextPageToken = document["nextPageToken"].GetString();
    if(document.HasMember("comments")) {
        for(rapidjson::Value::ConstMemberIterator itr = document["comments"].MemberBegin(); itr == document["comments"].MemberEnd(); itr++) {
            rapidjson::Document d;
            d.CopyFrom(itr->value, d.GetAllocator());
            this->comments.emplace_back(Comment(d));
        }
    }
}

string &CommentList::getKind() {
    return kind;
}

void CommentList::setKind(string &kind) {
    CommentList::kind = kind;
}

string &CommentList::getNextPageToken() {
    return nextPageToken;
}

void CommentList::setNextPageToken(string &nextPageToken) {
    CommentList::nextPageToken = nextPageToken;
}

vector<Comment> &CommentList::getComments() {
    return comments;
}

void CommentList::setComments(vector<Comment> &comments) {
    CommentList::comments = comments;
}
