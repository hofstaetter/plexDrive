//
// Created by Matthias Hofstätter on 14.09.17.
//

#include "changes/ChangesApi.h"

StartPageToken
ChangesApi::getStartPageToken(bool supportsTeamDrives, string teamDriveId, bool alt, string fields, bool prettyPrint,
                           string quotaUser, string userId) {
    if(GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    string responseBody;
    string responseHeaders;

    map<string, string> querystring = { make_pair("supportsTeamDrives", supportsTeamDrives ? "true" : "false"), make_pair("teamDriveId", teamDriveId),
                                        make_pair("alt", alt  ? "" : "json"), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
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
                         string teamDriveId, bool alt, string fields, bool prettyPrint, string quotaUser,
                         string userId) {
    if(GoogleOAuth::isAuthenticated()) {
        GoogleOAuth::authenticate();
    }

    string responseBody;
    string responseHeaders;

    map<string, string> querystring = { make_pair("pageToken", pageToken), make_pair("includeCorpusRemovals", includeCorpusRemovals ? "true" : "false"), make_pair("includeRemoved", includeRemoved ? "true" : "false"),
                                        make_pair("includeTeamDriveItems", includeTeamDriveItems ? "true" : "false"), make_pair("pageSize", to_string(pageSize)), make_pair("restrictToMyDrive", restrictToMyDrive ? "true" : "false"),
                                        make_pair("spaces", spaces), make_pair("supportsTeamDrives", supportsTeamDrives ? "true" : "false"), make_pair("teamDriveId", teamDriveId),
                                        make_pair("alt", alt  ? "" : "json"), make_pair("fields", fields), make_pair("prettyPrint", prettyPrint ? "true" : "false"), make_pair("quotaUser", quotaUser), make_pair("userId", userId) };
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
                       Channel requestBody, bool alt, string fields, bool prettyPrint, string quotaUser,
                       string userId) {
    return Channel();
}