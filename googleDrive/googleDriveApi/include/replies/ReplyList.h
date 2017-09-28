//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_REPLYLIST_H
#define PLEXDRIVE_REPLYLIST_H

#include <string>
#include <vector>
#include <replies/Reply.h>
#include <document.h>

class ReplyList {
private:
    string kind;
    string nextPageToken;
    vector<class Reply> replies;
public:
    ReplyList();
    ReplyList(rapidjson::Document &document);

    string &getKind();

    void setKind(string &kind);

    string &getNextPageToken();

    void setNextPageToken(string &nextPageToken);

    vector<Reply> &getReplies();

    void setReplies(vector<Reply> &replies);
};


#endif //PLEXDRIVE_REPLYLIST_H
