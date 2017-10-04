//
// Created by Matthias Hofstätter on 20.08.17.
//

#ifndef GOOGLEDRIVEAPI_GOOGLEDRIVEAPI_H
#define GOOGLEDRIVEAPI_GOOGLEDRIVEAPI_H

#include <curl/curl.h>
#include <rapidjson.h>
#include <document.h>
#include "File.h"
#include "GeneratedIds.h"
#include "FileList.h"
#include "channels/Channel.h"
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iostream>
#include "FilesApi.h"
#include "oauth/GoogleOAuth.h"
#include "channels/Channel.h"

using namespace std;

class FilesApi {
public:
    static class File copy(std::string fileId, bool ignoreDefaultVisibility, bool keepRevisionForever, std::string ocrLanguage, bool supportsTeamDrives, File &requestBody,
                                    string alt = "", std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static class File create(std::string uploadType, bool ignoreDefaultVisibility, bool keepRevisionForever, std::string ocrLanguage, bool supportsTeamDrives, bool useContentAsIndexableText, File requestBody,
                                      string alt = "", std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static bool del(string fileId, bool supportsTeamDrives,
                    string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static bool emptyTrash(string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static File exp(string fileId, string mimeType = "",
                             string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static class GeneratedIds generateIds(int count = 10, string space = "",
                                                 string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static File get(string fileId, bool acknowledgeAbuse = false, bool supportsTeamDrives = false,
                             string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static class FileList list(string corpora = "", string corpus = "", bool includeTeamDriveItems = false, string orderBy = "", int pageSize = 100, string pageToken = "", string q = "", string spaces = "", bool supportsTeamDrives = false,
                                   string teamDriveId = "",
                                   string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static File update(string fileId, string uploadType,  string addParents, bool keepRevisionForever, string ocrLanguage, string removeParents, bool supportsTeamDrives, bool useContentAsIndexableText, File &requestBody,
                                string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
    static class Channel watch(string fileId, bool acknowledgeAbuse, bool supportsTeamDrives, Channel& requestBody,
                                     string alt = "", string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
};


#endif //GOOGLEDRIVEAPI_GOOGLEDRIVEAPI_H
