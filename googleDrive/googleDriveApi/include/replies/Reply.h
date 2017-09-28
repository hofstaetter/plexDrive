//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_REPLIESRESOURCE_H
#define PLEXDRIVE_REPLIESRESOURCE_H


#include <ctime>
#include <User.h>

class Reply {
private:
    string kind;
    string id;
    time_t createdTime;
    time_t modifiedTime;
    User author;
    string htmlContent;
    string content;
    bool deleted;
    string action;
public:
    Reply();
    Reply(rapidjson::Document &document);

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

    string &getAction();
    void setAction(string &action);
};


#endif //PLEXDRIVE_REPLIESRESOURCE_H
