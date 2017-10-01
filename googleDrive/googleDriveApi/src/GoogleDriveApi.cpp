//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "GoogleDriveApi.h"
#include <curl/curl.h>
#include <string>
#include <oauth/GoogleOAuth.h>

using namespace std;

int GoogleDriveApi::VERBOSE;
string GoogleDriveApi::PATH;
string GoogleDriveApi::CONFIG_PATH;

void GoogleDriveApi::init(int verbose, string path) {
    GoogleDriveApi::VERBOSE = verbose;
    GoogleDriveApi::PATH = path;
    GoogleDriveApi::CONFIG_PATH = path + "/googleDriveApi.json";
}

void GoogleDriveApi::download(string fileId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    FILE *file;
    string responseheaders;
    int chunksize = 10485760;
    int filesize = -1;

    file = fopen(fileId.c_str(), "ab");
    while(ftell(file) < filesize) {
        if (file) {
            long responseCode = API::request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId),
                                             "GET",
                                             {make_pair("alt", "media")}, {make_pair("Authorization",
                                                                                     string("Bearer ").append(
                                                                                             GoogleOAuth::getAccessToken())),
                                                                           make_pair("Range", string("bytes=").append(
                                                                                   to_string(ftell(file))).append(
                                                                                   "-").append(to_string(
                                                                                   ftell(file) + chunksize)))}, {}, "",
                                             responseheaders, file);
            string len = responseheaders.substr(responseheaders.find("Content-Range: bytes"));
            len = len.substr(0, len.find("\r\n"));
            filesize = atoi(len.substr(len.find("/") + 1).c_str());

        }
    }
    fclose(file);
}
