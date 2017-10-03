//
// Created by Matthias Hofstätter on 20.08.17.
//

#include <thread>
#include <Response.h>
#include <Request.h>
#include "files/FilesApi.h"

using namespace std;

FileList
FilesApi::list(string corpora, string corpus, bool includeTeamDriveItems, string orderBy, int pageSize, string pageToken, string q, string spaces, bool supportsTeamDrives, string teamDriveId,
                     string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring;
    if(!corpora.empty()) querystring.insert(make_pair("corpora", corpora));
    if(!corpus.empty()) querystring.insert(make_pair("corpus", corpus));
    if(includeTeamDriveItems) querystring.insert(make_pair("includeTeamDriveItems", "true"));
    if(!orderBy.empty()) querystring.insert(make_pair("orderBy", orderBy));
    if(pageSize != 100) querystring.insert(make_pair("pageSize", to_string(pageSize)));
    if(!pageToken.empty()) querystring.insert(make_pair("pageToken", pageToken));
    if(!q.empty()) querystring.insert(make_pair("q", q));
    if(!spaces.empty()) querystring.insert(make_pair("spaces", spaces));
    if(supportsTeamDrives) querystring.insert(make_pair("supportsTeamDrive", "true"));
    if(!teamDriveId.empty()) querystring.insert(make_pair("teamDriveId", teamDriveId));

    if(!alt.empty()) querystring.insert(make_pair("alt", alt));
    if(!fields.empty()) querystring.insert(make_pair("fields", fields));
    if(!prettyPrint) querystring.insert(make_pair("prettyPrint", "false"));
    if(!quotaUser.empty()) querystring.insert(make_pair("quotaUser", quotaUser));
    if(!userId.empty()) querystring.insert(make_pair("userId", userId));

    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };
    Response response = Request("https://www.googleapis.com", "/drive/v3/files", "GET", querystring,
                                                headers, {}, "").execute();

    if(response.httpStatusCode != 200) { throw -1; }

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    //cout << responseJson["Files"].GetArray().Size() << endl;

    FileList lr(responseJson);

    return lr;
}

File
FilesApi::copy(string fileId, bool ignoreDefaultVisibility, bool keepRevisionForever, string ocrLanguage, bool supportsTeamDrives, File& requestBody,
                     string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    string responseBody;
    string responseHeaders;

    Response response = Request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId).append("/copy"), "POST", {}, {}, {}, requestBody.toString()).execute();

    if(response.httpStatusCode != 200) throw -1;

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    File fr(responseJson);

    return fr;
}

File
FilesApi::create(string uploadType, bool ignoreDefaultVisibility, bool keepRevisionForever, string ocrLanguage, bool supportsTeamDrives, bool useContentAsIndexableText, File& requestBody,
                       string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!(uploadType.compare("media") == 0 || uploadType.compare("multipart") == 0 || uploadType.compare("resumable") == 0)) {
        throw -1;
    }

    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("uploadType", uploadType), make_pair("ignoreDefaultVisibility", ignoreDefaultVisibility ? "true" : "false"), make_pair("keepRevisionForever", keepRevisionForever ? "true" : "false"),
                                        make_pair("ocrLanguage", ocrLanguage), make_pair("supportsTeamDrives", supportsTeamDrives ? "true" : "false"), make_pair("useContentAsIndexableText", useContentAsIndexableText ? "true" : "false"),
                                        make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", "/drive/v3/files/", "POST", querystring, headers, {}, requestBody.toString()).execute();

    if(response.httpStatusCode != 200) throw -1;

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    File fr(responseJson);

    return fr;
}

bool
FilesApi::del(string fileId, bool supportsTeamDrives,
                    string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("supportsTeamDrives", supportsTeamDrives ? "true" : "false"),
                                        make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId), "DELETE", querystring, headers, {}, "").execute();

    if(response.httpStatusCode != 204) return false;
    return true;
}

bool FilesApi::emptyTrash(string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", "/drive/v3/files/trash", "DELETE", querystring, headers, {}, "").execute();

    if(response.httpStatusCode == 204) return true;
    return false;
}

File
FilesApi::exp(string fileId, string mimeType,
                    string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("mimeType", mimeType),
                                        make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    //map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId).append("/export"), "GET", querystring, {}, {}, "").execute();

    if(response.httpStatusCode == 200) throw -1;

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    return File(responseJson);
}

GeneratedIds
FilesApi::generateIds(int count, string space, string alt, string fields, bool prettyPrint, string quotaUser,
                            string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("count", to_string(count)), make_pair("space", space),
                                        make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", "/drive/v3/files/generateIds", "GET", querystring, headers, {}, "").execute();

    if(response.httpStatusCode != 200) {
        throw -1;
    }

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    GeneratedIds gir(responseJson);

    return gir;
}

File
FilesApi::get(string fileId, bool acknowledgeAbuse, bool supportsTeamDrives, string alt, string fields,
                    bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring;

    if(acknowledgeAbuse) querystring.insert(make_pair("acknowledgeAbuse", "true"));
    if(supportsTeamDrives) querystring.insert(make_pair("supportsTeamDrives", "true"));

    //if(!alt.empty()) querystring.insert(make_pair("alt", alt));
    if(!fields.empty()) querystring.insert(make_pair("fields", fields));
    if(!prettyPrint) querystring.insert(make_pair("prettyPrint", "false"));
    if(!quotaUser.empty()) querystring.insert(make_pair("quotaUser", quotaUser));
    if(!userId.empty()) querystring.insert(make_pair("userId", userId));

    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId), "GET", querystring, headers, {}, "").execute();

    if(response.httpStatusCode != 200) {
        throw -1;
    }

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    File fr(responseJson);

    return fr;
}

File FilesApi::update(string fileId, string uploadType,  string addParents, bool keepRevisionForever, string ocrLanguage, string removeParents, bool supportsTeamDrives, bool useContentAsIndexableText, File& requestBody,
                                     string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("uploadType", uploadType), make_pair("addParents", addParents), make_pair("keepRevisionForever", keepRevisionForever ? "true" : "false"), make_pair("ocrLanguage", ocrLanguage),
                                        make_pair("removeParents", removeParents), make_pair("supportsTeamDrives", supportsTeamDrives ? "true" : "false"), make_pair("useContentAsIndexableText", useContentAsIndexableText ? "true" : "false"),
                                        make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    Response response = Request("https://www.googleapis.com", string("/drive/v3/files/").append(fileId), "GET", querystring, headers, {}, "").execute();

    if(response.httpStatusCode != 200) {
        throw -1;
    }

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(response.body.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    File fr(responseJson);

    return fr;
}

Channel
FilesApi::watch(string fileId, bool acknowledgeAbuse, bool supportsTeamDrives, Channel& requestBody,
                      string alt, string fields, bool prettyPrint, string quotaUser, string userId) {
    throw -2;
    //TODO implement
    /*if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    map<string, string> querystring = { make_pair("acknowledgeAbuse", acknowledgeAbuse ? "true" : "false"), make_pair("supportsTeamDrives", supportsTeamDrives ? "true" : "false"),
                                        make_pair("alt", alt), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    string responseBody;
    string responseHeaders;

    long responseCode = API::request("API://www.googleapis.com", string("/drive/v3/Files/").append(fileId), "GET", querystring, headers, {}, requestBody.toString(), responseHeaders, responseBody);

    if(responseCode != 200) throw -1;

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(responseBody.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    Channel c(responseJson);

    return c;*/
}
