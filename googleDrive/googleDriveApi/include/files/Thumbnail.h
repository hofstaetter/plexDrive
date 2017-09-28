//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_THUMBNAIL_H
#define PLEXDRIVE_THUMBNAIL_H

#include <string>
#include <document.h>

using namespace std;

class Thumbnail {
private:
    char image;
    string mimeType;

public:
    Thumbnail();
    Thumbnail(rapidjson::Document &document);

    char getImage();
    void setImage(char image);

    string &getMimeType();
    void setMimeType(string &mimeType);
};


#endif //PLEXDRIVE_THUMBNAIL_H
