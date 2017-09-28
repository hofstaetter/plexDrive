//
// Created by Matthias Hofstätter on 14.09.17.
//

#ifndef PLEXDRIVE_GETSTARTPAGETOKENRESPONSE_H
#define PLEXDRIVE_GETSTARTPAGETOKENRESPONSE_H

#include <string>
#include <document.h>

using namespace std;

class StartPageToken {
private:
    string kind;
    string startPageToken;
public:
    StartPageToken();
    StartPageToken(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getStartPageToken();
    void setStartPageToken(string &startPageToken);
};


#endif //PLEXDRIVE_GETSTARTPAGETOKENRESPONSE_H
