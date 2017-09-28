//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_ABOUT_H
#define PLEXDRIVE_ABOUT_H


#include <User.h>
#include "StorageQuota.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class About {
private:
    string kind;
    User user;
    StorageQuota storageQuota;
    //TODO importFormats
    //TODO exportFormats
    map<string, long> maxImportSizes;
    long maxUploadSize;
    bool appInstalled;
    vector<string> folderColorPalette;
public:
    About();
    About(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    User &getUser();
    void setUser(User &user);

    StorageQuota &getStorageQuota();
    void setStorageQuota(StorageQuota &storageQuota);

    map<string, long> &getMaxImportSizes();
    void setMaxImportSizes(map<string, long> &maxImportSizes);

    long getMaxUploadSize();
    void setMaxUploadSize(long maxUploadSize);

    bool isAppInstalled();
    void setAppInstalled(bool appInstalled);

    vector<string> &getFolderColorPalette();
    void setFolderColorPalette(vector<string> &folderColorPalette);
};


#endif //PLEXDRIVE_ABOUT_H
