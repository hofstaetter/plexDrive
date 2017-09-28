//
// Created by Matthias Hofstätter on 19.09.17.
//

#ifndef PLEXDRIVE_TEAMDRIVETHEMES_H
#define PLEXDRIVE_TEAMDRIVETHEMES_H

#include <string>
#include <document.h>

using namespace std;

class TeamDriveThemes {
private:
    string id;
    string backgroundImageLink;
    string colorRgb;
public:
    TeamDriveThemes();
    TeamDriveThemes(rapidjson::Document &document);

    string &getId();

    void setId(string &id);

    string &getBackgroundImageLink();

    void setBackgroundImageLink(string &backgroundImageLink);

    string &getColorRgb();

    void setColorRgb(string &colorRgb);
};


#endif //PLEXDRIVE_TEAMDRIVETHEMES_H
