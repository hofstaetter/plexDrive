//
// Created by Matthias Hofstätter on 21.08.17.
//

#include "files/File.h"
#include "document.h"
#include <vector>
#include <DateTime.h>

File::File() {
    //this->document = new rapidjson::Document;
}

File::File(rapidjson::Document& document) {
    cout << "[DEBUG] Creating File..." << endl;
    /*this->document = new rapidjson::Document;
    (*this->document).CopyFrom(document, (this->document)->GetAllocator());*/
    /*if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();*/
    if(document.HasMember("id"))
        this->id = document["id"].GetString();
    if(document.HasMember("name"))
        this->name = document["name"].GetString();
    if(document.HasMember("mimeType"))
        this->mimeType = document["mimeType"].GetString();
    /*if(document.HasMember("description"))
        this->description = document["description"].GetString();
    if(document.HasMember("starred"))
        this->starred = document["starred"].GetBool();
    if(document.HasMember("trashed"))
        this->trashed = document["trashed"].GetBool();
    if(document.HasMember("trashingUser")) {
        rapidjson::Document d(rapidjson::kObjectType);
        d.CopyFrom(document["trashingUser"], d.GetAllocator());
        this->trashingUser = User(d);
    }
    if(document.HasMember("trashedTime")) {
        this->trashedTime = document["trashedTime"].GetString();
    }*/
    if(document.HasMember("parents")) {
        for(auto &p : document["parents"].GetArray()) {
            this->parents.push_back(p.GetString());
        }
    }
    /*if(document.HasMember("properties")) {
        for(rapidjson::Value::ConstMemberIterator itr = document["properties"].MemberBegin(); itr == document["properties"].MemberEnd(); itr++) {
            this->properties.insert(make_pair(itr->name.GetString(), itr->value.GetString()));
        }
    }
    if(document.HasMember("appProperties")) {
        for(rapidjson::Value::ConstMemberIterator itr = document["appProperties"].MemberBegin(); itr == document["appProperties"].MemberEnd(); itr++) {
            this->appProperties.insert(make_pair(itr->name.GetString(), itr->value.GetString()));
        }
    }
    if(document.HasMember("spaces")) {
        for(auto &p : document["spaces"].GetArray()) {
            this->spaces.push_back(p.GetString());
        }
    }
    if(document.HasMember("version"))
        this->version = stol(document["version"].GetString());*/
    if(document.HasMember("webContentLink"))
        this->webContentLink = document["webContentLink"].GetString();
    /*if(document.HasMember("webViewLink"))
        this->webViewLink = document["webViewLink"].GetString();
    if(document.HasMember("iconLink"))
        this->iconLink = document["iconLink"].GetString();
    if(document.HasMember("hasThumbnail"))
        this->hasThumbnail = document["hasThumbnail"].GetBool();
    if(document.HasMember("thumbnailLink"))
        this->thumbnailLink = document["thumbnailLink"].GetString();*/

    if(document.HasMember("viewedByMeTime")) {
        string s = document["viewedByMeTime"].GetString();
        this->viewedByMeTime = DateTime::toEpoch(s);
    }

    if(document.HasMember("modifiedTime")) {
        string s = document["modifiedTime"].GetString();
        this->modifiedTime = DateTime::toEpoch(s);
    }

    if(document.HasMember("size"))
        this->size = stol(document["size"].GetString());
    cout << "[DEBUG] Created File with " << this->id << endl;
}

/*string &File::getKind() {
    return kind;
}

void File::setKind(string &kind) {
    File::kind = kind;
}*/

string File::getId() {
    return id;
}

void File::setId(string id) {
    File::id = id;
}

string File::getName() {
    return name;
}

void File::setName(string name) {
    File::name = name;
}

string File::getMimeType() {
    return mimeType;
}

void File::setMimeType(string mimeType) {
    File::mimeType = mimeType;
}

/*string &File::getDescription() {
    return description;
}

void File::setDescription(string &description) {
    File::description = description;
}

bool File::isStarred() {
    return starred;
}

void File::setStarred(bool starred) {
    File::starred = starred;
}

bool File::isTrashed() {
    return trashed;
}

void File::setTrashed(bool trashed) {
    File::trashed = trashed;
}

bool File::isExplicitlyTrashed() {
    return explicitlyTrashed;
}

void File::setExplicitlyTrashed(bool explicitlyTrashed) {
    File::explicitlyTrashed = explicitlyTrashed;
}

User &File::getTrashingUser() {
    return trashingUser;
}

void File::setTrashingUser(User &trashingUser) {
    File::trashingUser = trashingUser;
}*/

vector<string> File::getParents() {
    return parents;
}

void File::setParents(vector<string> parents) {
    File::parents = parents;
}

/*map<string, string> &File::getProperties() {
    return properties;
}

void File::setProperties(map<string, string> &properties) {
    File::properties = properties;
}

map<string, string> &File::getAppProperties() {
    return appProperties;
}

void File::setAppProperties(map<string, string> &appProperties) {
    File::appProperties = appProperties;
}

vector<string> &File::getSpaces() {
    return spaces;
}

void File::setSpaces(vector<string> &spaces) {
    File::spaces = spaces;
}

long File::getVersion() {
    return version;
}

void File::setVersion(long version) {
    File::version = version;
}*/

string File::getWebContentLink() {
    return webContentLink;
}

void File::setWebContentLink(string webContentLink) {
    File::webContentLink = webContentLink;
}

/*string &File::getWebViewLink() {
    return webViewLink;
}

void File::setWebViewLink(string &webViewLink) {
    File::webViewLink = webViewLink;
}

string &File::getIconLink() {
    return iconLink;
}

void File::setIconLink(string &iconLink) {
    File::iconLink = iconLink;
}

bool File::isHasThumbnail() {
    return hasThumbnail;
}

void File::setHasThumbnail(bool hasThumbnail) {
    File::hasThumbnail = hasThumbnail;
}

string &File::getThumbnailLink() {
    return thumbnailLink;
}

void File::setThumbnailLink(string &thumbnailLink) {
    File::thumbnailLink = thumbnailLink;
}*/

long File::getSize() {
    return size;
}

void File::setSize(long size) {
    File::size = size;
}

long File::getViewedByMeTime() {
    return viewedByMeTime;
}

void File::setViewedByMeTime(long viewedByMeTime) {
    File::viewedByMeTime = viewedByMeTime;
}

long File::getModifiedTime() {
    return modifiedTime;
}

void File::setModifiedTime(long modifiedTime) {
    File::modifiedTime = modifiedTime;
}

string File::toString() {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    this->toJSON().Accept(writer);

    string result(buffer.GetString());
    return result;
}

rapidjson::Document &File::toJSON() {
    rapidjson::Document d(rapidjson::kObjectType);

    //d.AddMember(rapidjson::StringRef("kind"), rapidjson::StringRef(this->kind.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("id"), rapidjson::StringRef(this->id.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef(this->name.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("mimeType"), rapidjson::StringRef(this->mimeType.c_str()), d.GetAllocator());
    //d.AddMember(rapidjson::StringRef("description"), rapidjson::StringRef(this->description.c_str()), d.GetAllocator());
    //d.AddMember(rapidjson::StringRef("starred"), rapidjson::Value(this->starred), d.GetAllocator());
    //d.AddMember(rapidjson::StringRef("trashed"), rapidjson::Value(this->trashed), d.GetAllocator());
    //d.AddMember(rapidjson::StringRef("explicitlyTrashed"), rapidjson::Value(this->explicitlyTrashed), d.GetAllocator());
    //d.AddMember(rapidjson::StringRef("trashingUser"), this->trashingUser.toJSON(), d.GetAllocator());
    //d.AddMember(rapidjson::StringRef("trashedTime"), rapidjson::StringRef(this->trashedTime.c_str()), d.GetAllocator());
    rapidjson::Value i(rapidjson::kArrayType);
    for(string &s : this->parents) {
        i.PushBack(rapidjson::StringRef(s.c_str()), d.GetAllocator());
    }
    d.AddMember(rapidjson::StringRef("parents"), i, d.GetAllocator());
    /*rapidjson::Value j(rapidjson::kObjectType);
    for(map<string, string>::iterator it = this->properties.begin(); it != this->properties.end(); ++it) {
        j.AddMember(rapidjson::StringRef(it->first.c_str()), rapidjson::StringRef(it->second.c_str()), d.GetAllocator());
    }
    d.AddMember(rapidjson::StringRef("properties"), j, d.GetAllocator());
    rapidjson::Value k(rapidjson::kObjectType);
    for(map<string, string>::iterator it = this->appProperties.begin(); it != this->appProperties.end(); ++it) {
        k.AddMember(rapidjson::StringRef(it->first.c_str()), rapidjson::StringRef(it->second.c_str()), d.GetAllocator());
    }
    d.AddMember(rapidjson::StringRef("appProperties"), k, d.GetAllocator());
    rapidjson::Value l(rapidjson::kArrayType);
    for(string &s : this->spaces) {
        l.PushBack(rapidjson::StringRef(s.c_str()), d.GetAllocator());
    }
    d.AddMember(rapidjson::StringRef("spaces"), l, d.GetAllocator());
    d.AddMember(rapidjson::StringRef("version"), rapidjson::Value((uint64_t)this->version), d.GetAllocator());*/
    d.AddMember(rapidjson::StringRef("webContentLink"), rapidjson::StringRef(this->webContentLink.c_str()), d.GetAllocator());
    /*d.AddMember(rapidjson::StringRef("webViewLink"), rapidjson::StringRef(this->webViewLink.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("iconLink"), rapidjson::StringRef(this->iconLink.c_str()), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("hasThumbnail"), rapidjson::Value(this->hasThumbnail), d.GetAllocator());
    d.AddMember(rapidjson::StringRef("trashedTime"), rapidjson::StringRef(this->trashedTime.c_str()), d.GetAllocator());*/
    //TODO
    d.AddMember(rapidjson::StringRef("viewedByMeTime"), rapidjson::StringRef(DateTime::fromEpoch(this->viewedByMeTime).c_str()), d.GetAllocator());
    //TODO
    d.AddMember(rapidjson::StringRef("modifiedTime"), rapidjson::StringRef(DateTime::fromEpoch(this->modifiedTime).c_str()), d.GetAllocator());
    //TODO
    d.AddMember(rapidjson::StringRef("size"), rapidjson::Value((uint64_t)this->size), d.GetAllocator());
    //TODO

    return d;
}

File::~File() {
    //cout << "[DEBUG] Destroying File with id " << this->id << "..." << endl;
}

/*string File::getKind() {
    return this->getString("kind");
}

void File::setKind(string &kind) {
    this->setString("kind", kind);
}

string File::getId() {
    return this->getString("id");
}

void File::setId(string &id) {
    this->setString("id", id);
}

string File::getName() {
    return this->getString("name");
}

void File::setName(string &name) {
    this->setString("name", name);
}

string File::getMimeType() {
    return this->getString("mimeType");
}

void File::setMimeType(string &mimeType) {
    this->setString("mimeType", mimeType);
}

string File::getDescription() {
    return this->getString("description");
}

void File::setDescription(string &description) {
    this->setString("description", description);
}

bool File::isStarred() {
    return this->getBool("starred");
}

void File::setStarred(bool starred) {
    this->setBool("starred", starred);
}

bool File::isTrashed() {
    return this->getBool("trashed");
}

void File::setTrashed(bool trashed) {
    this->setBool("trashed", trashed);
}

bool File::isExplicitlyTrashed() {
    return this->getBool("explicitlyTrashed");
}

void File::setExplicitlyTrashed(bool explicitlyTrashed) {
    this->setBool("explicitlyTrashed", explicitlyTrashed);
}

User File::getTrashingUser() {
    return this->getObject<User>("trashingUser");
}

void File::setTrashingUser(User trashingUser) {
    this->setObject("trashingUser", trashingUser);
}

string File::getTrashedTime() {
    return this->getString("trashedTime");
}

void File::setTrashedTime(string &trashedTime) {
    this->setString("trashedTime", trashedTime);
}

vector<string> File::getParents() {
    return this->getStringArray("parents");
}

void File::setParents(vector<string> &parents) {
    this->setStringArray("parents", parents);
}

map<string, string> File::getProperties() {
    return this->getStringMap("properties");
}

void File::setProperties(map<string, string> &properties) {
    this->setStringMap("properties", properties);
}

map<string, string> File::getAppProperties() {
    return this->getStringMap("appProperties");
}

void File::setAppProperties(map<string, string> &appProperties) {
    this->setStringMap("appProperties", appProperties);
}

vector<string> File::getSpaces() {
    return this->getStringArray("spaces");
}

void File::setSpaces(vector<string> &spaces) {
    this->setStringArray("spaces", spaces);
}

long File::getVersion() {
    return this->getLong("version");
}

void File::setVersion(long version) {
    this->setLong("version", version);
}

string File::getWebContentLink() {
    return this->getString("webContentLink");
}

void File::setWebContentLink(string &webContentLink) {
    this->setString("webContentLink", webContentLink);
}

string File::getWebViewLink() {
    return this->getString("webViewLink");
}

void File::setWebViewLink(string &webViewLink) {
    this->setString("webViewLink", webViewLink);
}

string File::getIconLink() {
    return this->getString("iconLink");
}

void File::setIconLink(string &iconLink) {
    this->setString("iconLink", iconLink);
}

bool File::isHasThumbnail() {
    return this->getBool("hasThumbnail");
}

void File::setHasThumbnail(bool hasThumbnail) {
    this->setBool("hasThumbnail", hasThumbnail);
}

string File::getThumbneilLink() {
    return this->getString("thumbneilLink");
}

void File::setThumbneilLink(string &thumbneilLink) {
    this->setString("thumbneilLink", thumbneilLink);
}

long File::getThumbneilVersion() {
    return this->getLong("thumbneilVersion");
}

void File::setThumbneilVersion(long thumbneilVersion) {
    this->setLong("thumbneilVersion", thumbneilVersion);
}

bool File::isViewedByMe() {
    return this->getBool("viewedByMe");
}

void File::setViewedByMe(bool viewedByMe) {
    this->setBool("viewedByMe", viewedByMe);
}

string File::getViewedByMeTime() {
    return this->getString("viewedByMeTime");
}

void File::setViewedByMeTime(string &viewedByMeTime) {
    this->setString("viewedByMeTime", viewedByMeTime);
}

string File::getCreatedTime() {
    return this->getString("createdTime");
}

void File::setCreatedTime(string &createdTime) {
    this->setString("createdTime", createdTime);
}

string File::getModifiedTime() {
    return this->getString("modifiedTime");
}

void File::setModifiedTime(string &modifiedTime) {
    this->setString("modifiedTime", modifiedTime);
}

string File::getModifiedByMeTime() {
    return this->getString("modifiedByMeTime");
}

void File::setModifiedByMeTime(string &modifiedByMeTime) {
    this->setString("modifiedByMeTime", modifiedByMeTime);
}

bool File::isModifiedByMe() {
    return this->getBool("modifiedByMe");
}

void File::setModifiedByMe(bool modifiedByMe) {
    this->setBool("modifiedByMe", modifiedByMe);
}

string File::getSharedWithMeTime() {
    return this->getString("sharedWithMeTime");
}

void File::setSharedWithMeTime(string &sharedWithMeTime) {
    this->setString("sharedWithMeTime", sharedWithMeTime);
}

User File::getSharingUser() {
    return User(this->getObject<User>("sharingUser"));
}

void File::setSharingUser(User sharingUser) {
    this->setObject("sharingUser", sharingUser);
}

vector<User> File::getOwners() {
    vector<User> result;
    vector<rapidjson::Document> vec = this->getObjectArray("owners");
    for(auto &d : ) {
        result.push_back(User(d));
    }
    return result;
}

void File::setOwners(vector<User> &owners) {
    std::vector<rapidjson::Document> v;
    for(User &u : owners) {
        v.push_back(u.document);
    }
    this->setObjectArray("owners", v);
}

string File::getTeamDriveId() {
    return this->getString("teamDriveId");
}

void File::setTeamDriveId(string &teamDriveId) {
    this->setString("teamDriveId", teamDriveId);
}

User File::getLastModifyingUser() {
    return this->getObject<User>("lastModifyingUser");
}

void File::setLastModifyingUser(User &lastModifyingUser) {
    this->setObject("lastModifyingUser", lastModifyingUser);
}

bool File::isShared() {
    return this->getBool("shared");
}

void File::setShared(bool shared) {
    this->setBool("shared", shared);
}

bool File::isOwnedByMe() {
    return this->getBool("ownedByMe");
}

void File::setOwnedByMe(bool ownedByMe) {
    this->setBool("ownedByMe", ownedByMe);
}

Capabilities File::getCapabilities() {
    return this->getObject<Capabilities>("Capabilities");
}

void File::setCapabilities(class Capabilities &Capabilities) {
    this->setObject("Capabilities", Capabilities);
}

bool File::isViewersCanCopyContent() {
    return this->getBool("viewersCanCopyContent");
}

void File::setViewersCanCopyContent(bool viewersCanCopyContent) {
    this->setBool("viewersCanCopyContent", viewersCanCopyContent);
}

bool File::isWritersCanShare() {
    return this->getBool("writersCanShare");
}

void File::setWritersCanShare(bool writersCanShare) {
    this->setBool("writersCanShare", writersCanShare);
}

vector<Permission> File::getPermissions() {
    vector<Permission> result;
    for(auto d : this->getObjectArray("Permissions")) {
        result.push_back(Permission(d));
    }
    return result;
}

void File::setPermissions(vector<Permission> &Permissions) {
    vector<rapidjson::Document> v;
    for(Permission &p : Permissions) {
        v.push_back(p.document);
    }
    this->setObjectArray("Permissions", v);
}

bool File::isHasAugmentedPermissions() {
    return this->getBool("hasAugmentedPermissions");
}

void File::setHasAugmentedPermissions(bool hasAugmentedPermissions) {
    this->setBool("hasAugmentedPermissions", hasAugmentedPermissions);
}

string File::getFolderColorRgb() {
    return this->getString("folderColorRgb");
}

void File::setFolderColorRgb(string &folderColorRgb) {
    this->setString("folderColorRgb", folderColorRgb);
}

string File::getOriginalFilename() {
    return this->getString("riginalFilename");
}

void File::setOriginalFilename(string &originalFilename) {
    this->setString("riginalFilename", originalFilename);
}

string File::getFullFileExtension() {
    return this->getString("fullFileExtension");
}

void File::setFullFileExtension(string &fullFileExtension) {
    this->setString("fullFileExtension", fullFileExtension);
}

string File::getFileExtension() {
    return this->getString("fileExtension");
}

void File::setFileExtension(string &fileExtension) {
    this->setString("fileExtension", fileExtension);
}

string File::getMd5Checksum() {
    return this->getString("md5Checksum");
}

void File::setMd5Checksum(string &md5Checksum) {
    this->setString("md5Checksum", md5Checksum);
}

long File::getSize() {
    return this->getLong("size");
}

void File::setSize(long size) {
    this->setLong("size", size);
}

long File::getQuotaBytesUser() {
    return this->getLong("quotaBytesUser");
}

void File::setQuotaBytesUser(long quotaBytesUser) {
    this->setLong("quotaBytesUser", quotaBytesUser);
}

string File::getHeadRevisionId() {
    return this->getString("headRevisionId");
}

void File::setHeadRevisionId(string &headRevisionId) {
    this->setString("headRevisionId", headRevisionId);
}

ImageMediaMetadata File::getImageMediaMetadata() {
    return this->getObject<ImageMediaMetadata>("ImageMediaMetadata");
}

void File::setImageMediaMetadata(class ImageMediaMetadata &ImageMediaMetadata) {
    this->setObject("ImageMediaMetadata", ImageMediaMetadata);
}

class VideoMediaMetadata File::getVideoMediaMetadata() {
    return this->getObject<VideoMediaMetadata>("VideoMediaMetadata");
}

void File::setVideoMediaMetadata(class VideoMediaMetadata &VideoMediaMetadata) {
    this->setObject("VideoMediaMetadata", VideoMediaMetadata);
}

bool File::isIsAppAuthorized() {
    return this->getBool("isAppAuthorized");
}

void File::setIsAppAuthorized(bool isAppAuthorized) {
    this->setBool("isAppAuthorized", isAppAuthorized);
}*/
