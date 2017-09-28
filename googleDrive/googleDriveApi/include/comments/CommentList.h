//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_COMMENTSLISTRESPONSE_H
#define PLEXDRIVE_COMMENTSLISTRESPONSE_H

#include <string>
#include <vector>
#include <comments/Comment.h>
#include <document.h>

using namespace std;

class CommentList {
private:
    string kind;
    string nextPageToken;
    vector<Comment> comments;
public:
    CommentList();
    CommentList(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getNextPageToken();
    void setNextPageToken(string &nextPageToken);

    vector<Comment> &getComments();
    void setComments(vector<Comment> &comments);
};


#endif //PLEXDRIVE_COMMENTSLISTRESPONSE_H
