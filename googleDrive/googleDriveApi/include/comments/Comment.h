//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_COMMENTSRESOURCE_H
#define PLEXDRIVE_COMMENTSRESOURCE_H


#include <ctime>
#include <string>
#include "User.h"

using namespace std;

class Comment {
private:
    string kind;
    string id;
    time_t createdTime;
    time_t modifiedTime;
    User author;
    string htmlContent;
    string content;
    bool deleted;
    bool resolved;
    //TODO
public:
    Comment();
    Comment(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getId();
    void setId(string &id);

    time_t getCreatedTime();
    void setCreatedTime(time_t createdTime);

    time_t getModifiedTime();
    void setModifiedTime(time_t modifiedTime);

    User &getAuthor();
    void setAuthor(User &author);

    string &getHtmlContent();
    void setHtmlContent(string &htmlContent);

    string &getContent();
    void setContent(string &content);

    bool isDeleted();
    void setDeleted(bool deleted);

    bool isResolved();
    void setResolved(bool resolved);
};


#endif //PLEXDRIVE_COMMENTSRESOURCE_H
