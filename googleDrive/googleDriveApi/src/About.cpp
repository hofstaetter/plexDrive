//
// Created by Matthias Hofstätter on 18.09.17.
//

#include "about/About.h"

About::About() {

}

About::About(rapidjson::Document &document) {
    throw -2;
}

string &About::getKind() {
    return kind;
}

void About::setKind(string &kind) {
    About::kind = kind;
}

User &About::getUser() {
    return user;
}

void About::setUser(User &user) {
    About::user = user;
}

StorageQuota &About::getStorageQuota() {
    return storageQuota;
}

void About::setStorageQuota(StorageQuota &storageQuota) {
    About::storageQuota = storageQuota;
}

map<string, long> &About::getMaxImportSizes() {
    return maxImportSizes;
}

void About::setMaxImportSizes(map<string, long> &maxImportSizes) {
    About::maxImportSizes = maxImportSizes;
}

long About::getMaxUploadSize() {
    return maxUploadSize;
}

void About::setMaxUploadSize(long maxUploadSize) {
    About::maxUploadSize = maxUploadSize;
}

bool About::isAppInstalled() {
    return appInstalled;
}

void About::setAppInstalled(bool appInstalled) {
    About::appInstalled = appInstalled;
}

vector<string> &About::getFolderColorPalette() {
    return folderColorPalette;
}

void About::setFolderColorPalette(vector<string> &folderColorPalette) {
    About::folderColorPalette = folderColorPalette;
}
