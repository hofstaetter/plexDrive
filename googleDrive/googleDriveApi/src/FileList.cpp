//
// Created by Matthias Hofstätter on 21.08.17.
//

#include <document.h>
#include <files/FileList.h>

FileList::FileList() {
}

FileList::FileList(rapidjson::Document &document) {
    if(document.HasMember("kind"))
        this->kind = document["kind"].GetString();
    if(document.HasMember("nextPageToken"))
        this->nextPageToken = document["nextPageToken"].GetString();
    if(document.HasMember("incompleteSearch"))
        this->incompleteSearch = document["incompleteSearch"].GetBool();
    if(document.HasMember("files")) {
        for(rapidjson::Value::ConstMemberIterator itr = document["files"].MemberBegin(); itr == document["files"].MemberEnd(); itr++) {
            rapidjson::Document d;
            d.CopyFrom(itr->value, d.GetAllocator());
            this->files.emplace_back(File(d));
        }
    }
}

string &FileList::getKind() {
    return kind;
}

void FileList::setKind(string &kind) {
    FileList::kind = kind;
}

string &FileList::getNextPageToken() {
    return nextPageToken;
}

void FileList::setNextPageToken(string &nextPageToken) {
    FileList::nextPageToken = nextPageToken;
}

bool FileList::isIncompleteSearch() {
    return incompleteSearch;
}

void FileList::setIncompleteSearch(bool incompleteSearch) {
    FileList::incompleteSearch = incompleteSearch;
}

vector<File> &FileList::getFiles() {
    return files;
}

void FileList::setFiles(vector<File> &files) {
    FileList::files = files;
}

/*string FileList::getKind() {
    return this->getString("kind");
}

void FileList::setKind(string kind) {
    this->setString("kind", kind);
}

string FileList::getNextPageToken() {
    return this->getString("nextPageToken");
}

void FileList::setNextPageToken(string nextPageToken) {
    this->setString("nextPageToken", nextPageToken);
}

bool FileList::isIncompleteSearch() {
    return this->getBool("incompleteSearch");
}

void FileList::setIncompleteSearch(bool incompleteSearch) {
    this->setBool("incompleteSearch", incompleteSearch);
}

vector<class File> FileList::getFiles() {
    vector<File> result;
    vector<File> docs = this->getObjectArray<File>("Files");

    for(int i = 0; i < docs.size(); i++) {
        result.push_back(docs[i]);
    }

    return result;
}

void FileList::setFiles(vector<class File> Files) {
    this->setObjectArray<File>("Files", Files);
}*/

