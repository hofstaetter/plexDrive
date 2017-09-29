//
// Created by Matthias Hofstätter on 14.09.17.
//

#include "changes/ChangesApi.h"

StartPageToken
ChangesApi::getStartPageToken(bool supportsTeamDrives, string teamDriveId, string alt, string fields, bool prettyPrint,
                           string quotaUser, string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    string responseBody;
    string responseHeaders;

    map<string, string> querystring;
    if(supportsTeamDrives) querystring.insert(make_pair("supportsTeamDrives", "true"));
    if(!teamDriveId.empty()) querystring.insert(make_pair("teamDriveId", teamDriveId));

    if(!alt.empty()) querystring.insert(make_pair("alt", alt));
    if(!fields.empty()) querystring.insert(make_pair("fields", fields));
    if(!prettyPrint) querystring.insert(make_pair("prettyPrint", "false"));
    if(!quotaUser.empty()) querystring.insert(make_pair("quotaUser", quotaUser));
    if(!userId.empty()) querystring.insert(make_pair("userId", userId));

    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    long responseCode = API::request("https://www.googleapis.com", "/drive/v3/changes/startPageToken", "GET", querystring, headers, {}, "", responseHeaders, responseBody);

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(responseBody.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    if(responseCode != 200) throw responseJson;

    return StartPageToken(responseJson);
}

ChangeList ChangesApi::list(string pageToken, bool includeCorpusRemovals, bool includeRemoved, bool includeTeamDriveItems,
                         int pageSize, bool restrictToMyDrive, string spaces, bool supportsTeamDrives,
                         string teamDriveId, string alt, string fields, bool prettyPrint, string quotaUser,
                         string userId) {
    if(!GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    string responseBody;
    string responseHeaders;

    map<string, string> querystring = { make_pair("pageToken", pageToken) };
    if(includeCorpusRemovals) querystring.insert(make_pair("includeCorpusRemovals", "true"));
    if(!includeRemoved) querystring.insert(make_pair("includeRemoved", "false"));
    if(includeTeamDriveItems) querystring.insert(make_pair("includeTeamDriveItems", "true"));
    if(pageSize != 100) querystring.insert(make_pair("pageSize", to_string(pageSize)));
    if(restrictToMyDrive) querystring.insert(make_pair("restrictToMyDrive", "true"));
    if(!spaces.empty()) querystring.insert(make_pair("spaces", spaces));
    if(supportsTeamDrives) querystring.insert(make_pair("supportsTeamDrives", "true"));
    if(!teamDriveId.empty()) querystring.insert(make_pair("teamDriveId", teamDriveId));

    if(!alt.empty()) querystring.insert(make_pair("alt", alt));
    if(!fields.empty()) querystring.insert(make_pair("fields", fields));
    if(!prettyPrint) querystring.insert(make_pair("prettyPrint", "false"));
    if(!quotaUser.empty()) querystring.insert(make_pair("quotaUser", quotaUser));
    if(!userId.empty()) querystring.insert(make_pair("userId", userId));

    map<string, string> headers = { make_pair("Authorization", string("Bearer ").append(GoogleOAuth::getAccessToken())) };

    long responseCode = API::request("https://www.googleapis.com", "/drive/v3/changes", "GET", querystring, headers, {}, "", responseHeaders, responseBody);

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(responseBody.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    if(responseCode != 200) throw responseJson;

    return ChangeList(responseJson);
}

Channel ChangesApi::watch(string pageToken, bool includeCorpusRemovals, bool includeRemoved, bool includeTeamDriveItems,
                       int pageSize, bool restrictToMyDrive, string spaces, bool supportsTeamDrives, string teamDriveId,
                       Channel requestBody, string alt, string fields, bool prettyPrint, string quotaUser,
                       string userId) {
    return Channel();
}