//
// Created by Matthias Hofstätter on 11.09.17.
//

#ifndef GOOGLEDRIVEAPI_GOOGLEAPIAUTH_H
#define GOOGLEDRIVEAPI_GOOGLEAPIAUTH_H

#include <string>
#include <rapidjson.h>
#include <document.h>
#include <files/FilesApi.h>
#include <API.h>

using namespace std;

class GoogleOAuth {
public:
    static string &getAccessToken();

    static void authenticate();
    static bool isAuthenticated();
private:
    static string clientId;
    static string clientSecret;
    static string authorizationCode;
    static string refreshToken;
    static string accessToken;
    static time_t expire;

    static void requestAuthorizationCode(string clientId, string redirectUri, string responseType, string scope, string state, string includeGrantedScopes, string loginHint, string prompt);
    static void requestTokens(string clientId, string clientSecret);
    static void refreshAccessToken(string clientSecret, string grantType, string refreshToken, string clientId);
};


#endif //GOOGLEDRIVEAPI_GOOGLEAPIAUTH_H
