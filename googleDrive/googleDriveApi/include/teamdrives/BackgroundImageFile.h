//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_BACKGROUNDIMAGEFILE_H
#define PLEXDRIVE_BACKGROUNDIMAGEFILE_H

#include <string>
#include <document.h>

using namespace std;

class BackgroundImageFile {
private:
    string id;
    float xCoordinate;
    float yCoordinate;
    float width;
public:
    BackgroundImageFile();
    BackgroundImageFile(rapidjson::Document &document);

    string &getId();

    void setId(string &id);

    float getXCoordinate();

    void setXCoordinate(float xCoordinate);

    float getYCoordinate();

    void setYCoordinate(float yCoordinate);

    float getWidth();

    void setWidth(float width);

    /*string getId();

    void setId(string id);

    float getXCoordinate();

    void setXCoordinate(float xCoordinate);

    float getYCoordinate();

    void setYCoordinate(float yCoordinate);

    float getWidth();

    void setWidth(float width);*/
};


#endif //PLEXDRIVE_BACKGROUNDIMAGEFILE_H
