//
// Created by Matthias Hofstätter on 21.08.17.
//

#ifndef GOOGLEDRIVEAPI_LISTRESPONSE_H
#define GOOGLEDRIVEAPI_LISTRESPONSE_H

#include "files/FilesApi.h"
#include "File.h"
#include <rapidjson.h>
#include <document.h>
#include <writer.h>
#include <pointer.h>
#include <string>
#include <vector>

using namespace std;

class FileList {
private:
    string kind;
    string nextPageToken;
    bool incompleteSearch;
    vector<class File> files;
public:
    FileList();
    FileList(rapidjson::Document& document);

    string &getKind();
    void setKind(string &kind);

    string &getNextPageToken();
    void setNextPageToken(string &nextPageToken);

    bool isIncompleteSearch();
    void setIncompleteSearch(bool incompleteSearch);

    vector<File> getFiles();
    void setFiles(vector<File> files);
};


#endif //GOOGLEDRIVEAPI_LISTRESPONSE_H
