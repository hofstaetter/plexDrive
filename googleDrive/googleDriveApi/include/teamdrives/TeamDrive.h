//
// Created by Matthias Hofstätter on 14.09.17.
//

#ifndef PLEXDRIVE_TEAMDRIVESRESOURCE_H
#define PLEXDRIVE_TEAMDRIVESRESOURCE_H

#include <string>
#include <teamdrives/BackgroundImageFile.h>
#include <Capabilities.h>

using namespace std;

class TeamDrive {
private:
    string kind;
    string name;
    string themeId;
    string colorRgb;
    class BackgroundImageFile backgroundImageFile;
    string backgroundImageLink;
    class Capabilities capabilities;
public:
    TeamDrive();
    TeamDrive(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getName();
    void setName(string &name);

    string &getThemeId();
    void setThemeId(string &themeId);

    string &getColorRgb();
    void setColorRgb(string &colorRgb);

    class BackgroundImageFile &getBackgroundImageFile();
    void setBackgroundImageFile(class BackgroundImageFile &backgroundImageFile);

    string &getBackgroundImageLink();
    void setBackgroundImageLink(string &backgroundImageLink);

    class Capabilities &getCapabilities();
    void setCapabilities(class Capabilities &capabilities);
};


#endif //PLEXDRIVE_TEAMDRIVESRESOURCE_H
