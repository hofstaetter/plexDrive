//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_REVISION_H
#define PLEXDRIVE_REVISION_H


#include <ctime>
#include <User.h>

class Revision {
private:
    string kind;
    string id;
    string mimeType;
    string modifiedTime;
    bool keepForever;
    bool publishAuto;
    bool publishedOutsideDomain;
    User lastModifyingUser;
    string originalFilename;
    string md5Checksum;
    long size;
public:
    Revision();
    Revision(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getId();
    void setId(string &id);

    string &getMimeType();
    void setMimeType(string &mimeType);

    string &getModifiedTime();
    void setModifiedTime(string &modifiedTime);

    bool isKeepForever();
    void setKeepForever(bool keepForever);

    bool isPublishAuto();
    void setPublishAuto(bool publishAuto);

    bool isPublishedOutsideDomain();
    void setPublishedOutsideDomain(bool publishedOutsideDomain);

    User &getLastModifyingUser();
    void setLastModifyingUser(User &lastModifyingUser);

    string &getOriginalFilename();
    void setOriginalFilename(string &originalFilename);

    string &getMd5Checksum();
    void setMd5Checksum(string &md5Checksum);

    long getSize();
    void setSize(long size);
};

#endif //PLEXDRIVE_REVISION_H
