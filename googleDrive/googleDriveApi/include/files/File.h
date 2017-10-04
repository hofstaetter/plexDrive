//
// Created by Matthias Hofstätter on 21.08.17.
//

#ifndef GOOGLEDRIVEAPI_FILESRESOURCE_H
#define GOOGLEDRIVEAPI_FILESRESOURCE_H

#include "files/FilesApi.h"
#include "User.h"
#include "files/ImageMediaMetadata.h"
#include "files/VideoMediaMetadata.h"
#include "Capabilities.h"
#include "permissions/Permission.h"
#include "rapidjson.h"
#include "document.h"
#include "writer.h"

#include <string>
#include <map>
#include <vector>

using namespace std;

class File {
private:
    string kind;
    string id;
    string name;
    string mimeType;
    //string description;
    //bool starred;
    //bool trashed;
    //bool explicitlyTrashed;
    //User trashingUser;
    //string trashedTime;
    vector<string> parents;
    //map<string, string> properties;
    //map<string, string> appProperties;
    //vector<string> spaces;
    //long version;
    string webContentLink;
    //string webViewLink;
    //string iconLink;
    //bool hasThumbnail;
    string thumbnailLink;
    //TODO
    long viewedByMeTime;
    //TODO
    long modifiedTime;
    //TODO
    long size;
    //TODO

public:
    File();
    File(rapidjson::Document& document);

    string toString();
    rapidjson::Document &toJSON();

    /*string &getKind();
    void setKind(string &kind);*/

    string getId();
    void setId(string id);

    string getName();
    void setName(string name);

    string getMimeType();
    void setMimeType(string mimeType);

    /*string &getDescription();
    void setDescription(string &description);

    bool isStarred();
    void setStarred(bool starred);

    bool isTrashed();
    void setTrashed(bool trashed);

    bool isExplicitlyTrashed();
    void setExplicitlyTrashed(bool explicitlyTrashed);

    User &getTrashingUser();
    void setTrashingUser(User &trashingUser);

    time_t getTrashedTime();
    void setTrashedTime(time_t trashedTime);*/

    vector<string> getParents();
    void setParents(vector<string> parents);

    /*map<string, string> &getProperties();
    void setProperties(map<string, string> &properties);

    map<string, string> &getAppProperties();
    void setAppProperties(map<string, string> &appProperties);

    vector<string> &getSpaces();
    void setSpaces(vector<string> &spaces);

    long getVersion();
    void setVersion(long version);*/

    string getWebContentLink();
    void setWebContentLink(string webContentLink);

    /*string &getWebViewLink();
    void setWebViewLink(string &webViewLink);

    string &getIconLink();
    void setIconLink(string &iconLink);

    bool isHasThumbnail();
    void setHasThumbnail(bool hasThumbnail);

    string &getThumbnailLink();
    void setThumbnailLink(string &thumbnailLink);*/

    long getViewedByMeTime();
    void setViewedByMeTime(long viewedByMeTime);

    long getModifiedTime();
    void setModifiedTime(long modifiedTime);

    long getSize();
    void setSize(long size);
    //TODO

    /*string getKind();

    void setKind(string &kind);

    string getId();

    void setId(string &id);

    string getName();

    void setName(string &name);

    string getMimeType();

    void setMimeType(string &mimeType);

    string getDescription();

    void setDescription(string &description);

    bool isStarred();

    void setStarred(bool starred);

    bool isTrashed();

    void setTrashed(bool trashed);

    bool isExplicitlyTrashed();

    void setExplicitlyTrashed(bool explicitlyTrashed);

    User getTrashingUser();

    void setTrashingUser(User trashingUser);

    string getTrashedTime();

    void setTrashedTime(string &trashedTime);

    vector<string> getParents();

    void setParents(vector<string> &parents);

    map<string, string> getProperties();

    void setProperties(map<string, string> &properties);

    map<string, string> getAppProperties();

    void setAppProperties(map<string, string> &appProperties);

    vector<string> getSpaces();

    void setSpaces(vector<string> &spaces);

    long getVersion();

    void setVersion(long version);

    string getWebContentLink();

    void setWebContentLink(string &webContentLink);

    string getWebViewLink();

    void setWebViewLink(string &webViewLink);

    string getIconLink();

    void setIconLink(string &iconLink);

    bool isHasThumbnail();

    void setHasThumbnail(bool hasThumbnail);

    string getThumbneilLink();

    void setThumbneilLink(string &thumbneilLink);

    long getThumbneilVersion();

    void setThumbneilVersion(long thumbneilVersion);

    bool isViewedByMe();

    void setViewedByMe(bool viewedByMe);

    string getViewedByMeTime();

    void setViewedByMeTime(string &viewedByMeTime);

    string getCreatedTime();

    void setCreatedTime(string &createdTime);

    string getModifiedTime();

    void setModifiedTime(string &modifiedTime);

    string getModifiedByMeTime();

    void setModifiedByMeTime(string &modifiedByMeTime);

    bool isModifiedByMe();

    void setModifiedByMe(bool modifiedByMe);

    string getSharedWithMeTime();

    void setSharedWithMeTime(string &sharedWithMeTime);

    User getSharingUser();

    void setSharingUser(User sharingUser);

    vector<User> getOwners();

    void setOwners(vector<User> &owners);

    string getTeamDriveId();

    void setTeamDriveId(string &teamDriveId);

    User getLastModifyingUser();

    void setLastModifyingUser(User &lastModifyingUser);

    bool isShared();

    void setShared(bool shared);

    bool isOwnedByMe();

    void setOwnedByMe(bool ownedByMe);

    class Capabilities getCapabilities();

    void setCapabilities(class Capabilities &Capabilities);

    bool isViewersCanCopyContent();

    void setViewersCanCopyContent(bool viewersCanCopyContent);

    bool isWritersCanShare();

    void setWritersCanShare(bool writersCanShare);

    vector<Permission> getPermissions();

    void setPermissions(vector<Permission> &Permissions);

    bool isHasAugmentedPermissions();

    void setHasAugmentedPermissions(bool hasAugmentedPermissions);

    string getFolderColorRgb();

    void setFolderColorRgb(string &folderColorRgb);

    string getOriginalFilename();

    void setOriginalFilename(string &originalFilename);

    string getFullFileExtension();

    void setFullFileExtension(string &fullFileExtension);

    string getFileExtension();

    void setFileExtension(string &fileExtension);

    string getMd5Checksum();

    void setMd5Checksum(string &md5Checksum);

    long getSize();

    void setSize(long size);

    long getQuotaBytesUser();

    void setQuotaBytesUser(long quotaBytesUser);

    string getHeadRevisionId();

    void setHeadRevisionId(string &headRevisionId);

    class ImageMediaMetadata getImageMediaMetadata();

    void setImageMediaMetadata(class ImageMediaMetadata &ImageMediaMetadata);

    class VideoMediaMetadata getVideoMediaMetadata();

    void setVideoMediaMetadata(class VideoMediaMetadata &VideoMediaMetadata);

    bool isIsAppAuthorized();

    void setIsAppAuthorized(bool isAppAuthorized);

    bool isAppAuthorized;*/
};


#endif //GOOGLEDRIVEAPI_FILESRESOURCE_H
