//
// Created by Matthias Hofstätter on 21.08.17.
//

#ifndef GOOGLEDRIVEAPI_LISTRESPONSE_H
#define GOOGLEDRIVEAPI_LISTRESPONSE_H

#include "files/Files.h"
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

    vector<class File> &getFiles();
    void setFiles(vector<class File> &files);
};


#endif //GOOGLEDRIVEAPI_LISTRESPONSE_H
