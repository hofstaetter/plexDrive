//
// Created by Matthias Hofstätter on 11.09.17.
//

#include <fstream>
#include <GoogleDriveApi.h>
#include "oauth/GoogleOAuth.h"

using namespace std;

string GoogleOAuth::clientId;
string GoogleOAuth::clientSecret;
string GoogleOAuth::authorizationCode;
string GoogleOAuth::refreshToken;
string GoogleOAuth::accessToken = "";
time_t GoogleOAuth::expire;

void GoogleOAuth::requestAuthorizationCode(string clientId, string redirectUri, string responseType, string scope, string state, string includeGrantedScopes,
                                           string loginHint, string prompt) {
    string responseBody;
    string responseHeaders;
    long httpcode = API::request("https://accounts.google.com", "/o/oauth2/v2/auth", "POST", { make_pair("response_type", responseType), make_pair("client_id", clientId), make_pair("redirect_uri", redirectUri),
                                                                                                 make_pair("scope", scope) }, {},
                                            {}, //{ make_pair("code", authCode), make_pair("client_id", clientId), make_pair("client_secret", clientSecret), make_pair("redirect_uri", "urn:ietf:wg:oauth:2.0:oob"), make_pair("grant_type", "authorization_code") },
                                            "", responseHeaders, responseBody);

      if(httpcode != 302) { throw -1; }

    cout << "Please visit following URL and paste the AuthCode below: " << responseHeaders.substr(responseHeaders.find("Location", 0) + 10, responseHeaders.find("\r\n", responseHeaders.find("Location", 0)) - responseHeaders.find("Location", 0) - 10) << endl;
    cin >> GoogleOAuth::authorizationCode;

    GoogleOAuth::clientId = clientId;
}

void GoogleOAuth::requestTokens(string clientId, string clientSecret) {
    if(GoogleOAuth::authorizationCode.empty() || GoogleOAuth::clientId.empty()) {
        throw -1;
    }

    string responseHeaders;
    string responseBody;
    long httpcode = API::request("https://www.googleapis.com", "/oauth2/v4/token", "POST", { make_pair("prettyPrint", "false") },
                                            { },
                                            { make_pair("grant_type", "authorization_code"), make_pair("code", GoogleOAuth::authorizationCode), make_pair("redirect_uri", "urn:ietf:wg:oauth:2.0:oob"), make_pair("client_id", clientId), make_pair("client_secret", clientSecret) }, //{ make_pair("code", authCode), make_pair("client_id", clientId), make_pair("client_secret", clientSecret), make_pair("redirect_uri", "urn:ietf:wg:oauth:2.0:oob"), make_pair("grant_type", "authorization_code") },
                                            "", responseHeaders, responseBody);
    //{ make_pair("grant_type", "authorization_code"), make_pair("code", authCode), make_pair("redirect_uri", "urn:ietf:wg:oauth:2.0:oob"), make_pair("client_id", clientId), make_pair("client_secret", clientSecret) }

    if(httpcode != 200) { throw responseBody; }

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(responseBody.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    if(responseJson.IsObject() && responseJson.HasMember("refresh_token") && responseJson.HasMember("access_token")) {
        GoogleOAuth::refreshToken = responseJson["refresh_token"].GetString();
        GoogleOAuth::accessToken = responseJson["access_token"].GetString();
        GoogleOAuth::expire = time(NULL) + 3600;
    } else { throw responseJson; }
}

void GoogleOAuth::refreshAccessToken(string clientSecret, string grantType, string refreshToken, string clientId) {
    if(GoogleOAuth::authorizationCode.empty() || GoogleOAuth::clientId.empty() || GoogleOAuth::refreshToken.empty()) {
        throw -1;
    }

    if(!GoogleOAuth::refreshToken.empty() && GoogleOAuth::expire > time(NULL)) {
        return;
    }

    string responseHeaders;
    string responseBody;

    long httpcode = API::request("https://www.googleapis.com", "/oauth2/v4/token", "POST", { make_pair("prettyPrint", "false") },
                                 { },
                                   { make_pair("grant_type", "refresh_token"), make_pair("refresh_token", GoogleOAuth::refreshToken), make_pair("client_id", clientId), make_pair("client_secret", clientSecret) }, //{ make_pair("code", authCode), make_pair("client_id", clientId), make_pair("client_secret", clientSecret), make_pair("redirect_uri", "urn:ietf:wg:oauth:2.0:oob"), make_pair("grant_type", "authorization_code") },
                                   "", responseHeaders, responseBody);

    rapidjson::Document responseJson;
    rapidjson::ParseResult pr = responseJson.Parse(responseBody.c_str());
    if(!pr) {
        printf("PARSE ERROR");
    }

    if(responseJson.IsObject() && responseJson.HasMember("access_token")) {
        GoogleOAuth::accessToken = responseJson["access_token"].GetString();
        GoogleOAuth::expire = time(NULL) + 3600;
    } else { throw responseJson; }
}

void GoogleOAuth::authenticate() {
    rapidjson::Document configuration(rapidjson::kObjectType);
    ifstream file(GoogleDriveApi::CONFIG_PATH);
    if(file.is_open()) {
        string configurationstring;
        file >> configurationstring;
        file.close();

        configuration.Parse(configurationstring.c_str());
        if (configuration.IsObject()) {
            if (configuration.HasMember("clientId"))
                GoogleOAuth::clientId = configuration["clientId"].GetString();
            if (configuration.HasMember("clientSecret"))
                GoogleOAuth::clientSecret = configuration["clientSecret"].GetString();
            if (configuration.HasMember("authorizationCode"))
                GoogleOAuth::authorizationCode = configuration["authorizationCode"].GetString();
            if (configuration.HasMember("accessToken"))
                GoogleOAuth::accessToken = configuration["accessToken"].GetString();
            if (configuration.HasMember("refreshToken"))
                GoogleOAuth::refreshToken = configuration["refreshToken"].GetString();
        }
    }

    if(!GoogleOAuth::refreshToken.empty()) { //access token only expired
        GoogleOAuth::refreshAccessToken(GoogleOAuth::clientSecret, "refresh_token", GoogleOAuth::refreshToken, GoogleOAuth::clientId);
    } else {
        if(GoogleOAuth::authorizationCode.empty()) {
            printf("Please enter your client ID: ");
            cin >> GoogleOAuth::clientId;
            printf("Please enter your client secret: ");
            cin >> GoogleOAuth::clientSecret;
            GoogleOAuth::requestAuthorizationCode(GoogleOAuth::clientId, "urn:ietf:wg:oauth:2.0:oob", "code", "https://www.googleapis.com/auth/drive", "", "", "", "");
        }
        GoogleOAuth::requestTokens(GoogleOAuth::clientId, GoogleOAuth::clientSecret);
    }

    if(GoogleOAuth::isAuthenticated()) {
        rapidjson::Document configuration(rapidjson::kObjectType);
        configuration.AddMember(rapidjson::StringRef("clientId"), rapidjson::StringRef(GoogleOAuth::clientId.c_str()), configuration.GetAllocator());
        configuration.AddMember(rapidjson::StringRef("clientSecret"), rapidjson::StringRef(GoogleOAuth::clientSecret.c_str()), configuration.GetAllocator());
        configuration.AddMember(rapidjson::StringRef("authorizationCode"), rapidjson::StringRef(GoogleOAuth::authorizationCode.c_str()), configuration.GetAllocator());
        configuration.AddMember(rapidjson::StringRef("accessToken"), rapidjson::StringRef(GoogleOAuth::accessToken.c_str()), configuration.GetAllocator());
        configuration.AddMember(rapidjson::StringRef("refreshToken"), rapidjson::StringRef(GoogleOAuth::refreshToken.c_str()), configuration.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        configuration.Accept(writer);

        string configurationstring = buffer.GetString();
        ofstream file(GoogleDriveApi::CONFIG_PATH);
        file << configurationstring;
        file.close();
    }
}

bool GoogleOAuth::isAuthenticated() {
    if(!GoogleOAuth::accessToken.empty() && GoogleOAuth::expire > time(NULL)) {
        /*string responseHeaders;
        string responseBody;

        long httpcode = API::request("https://www.googleapis.com", "/oauth2/v3/tokeninfo", "POST", { },
                                       { make_pair("content-type", "application/x-www-form-urlencoded") },
                                       { make_pair("access_token", GoogleOAuth::accessToken) }, //, make_pair("refresh_token", GoogleOAuth::refreshToken), make_pair("client_id", clientId), make_pair("client_secret", clientSecret) }, //{ make_pair("code", authCode), make_pair("client_id", clientId), make_pair("client_secret", clientSecret), make_pair("redirect_uri", "urn:ietf:wg:oauth:2.0:oob"), make_pair("grant_type", "authorization_code") },
                                       "", responseHeaders, responseBody);

        rapidjson::Document responseJson;
        rapidjson::ParseResult pr = responseJson.Parse(responseBody.c_str());
        if(!pr) {
            printf("PARSE ERROR");
        }

        if(responseJson.IsObject() && responseJson.HasMember("azp") && responseJson.HasMember("expires_in")) {
            if(responseJson["azp"].GetString() != GoogleOAuth::clientId || atoi(responseJson["expires_in"].GetString()) <= 0) return false;
        } else { throw responseJson; }*/

        return true;
    }
    return false;
}

string &GoogleOAuth::getAccessToken() {
    return GoogleOAuth::accessToken;
}

