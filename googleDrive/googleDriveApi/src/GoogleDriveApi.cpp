//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "GoogleDriveApi.h"
#include <curl/curl.h>
#include <string>
#include <oauth/GoogleOAuth.h>
#include <fstream>
#include <Response.h>
#include <Request.h>
#include <sys/stat.h>
#include <thread>

using namespace std;

int VERBOSE = 0;
string PATH = ".";
string CONFIG_PATH = ".";

void GoogleDriveApi::init(int verbose, string path) {
    ::VERBOSE = verbose;
    ::PATH = path;
    ::CONFIG_PATH = path + "/googleDriveApi.json";
}

string GoogleDriveApi::download(string fileId, long from, long to) {
    if (!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    return Request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId), "GET", { make_pair("alt", "media")}, {make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())), make_pair("Range", string("bytes=").append(to_string(from)).append("-").append(to_string(to)))}, {}, "").execute().body;
}
