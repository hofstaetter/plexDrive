//
// Created by Matthias Hofstätter on 21.08.17.
//

#ifndef GOOGLEDRIVEAPI_GENERATEIDSRESPONSE_H
#define GOOGLEDRIVEAPI_GENERATEIDSRESPONSE_H

#include "files/FilesApi.h"
#include <string>
#include <vector>
#include <document.h>

using namespace std;

class GeneratedIds {
private:
    string kind;
    string space;
    vector<string> ids;

public:
    GeneratedIds();
    GeneratedIds(rapidjson::Document& document);

    string &getKind();
    void setKind(string &kind);

    string &getSpace();
    void setSpace(string &space);

    vector<string> &getIds();
    void setIds(vector<string> &ids);
};


#endif //GOOGLEDRIVEAPI_GENERATEIDSRESPONSE_H
