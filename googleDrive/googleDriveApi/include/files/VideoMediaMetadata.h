//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_VIDEOMEDIAMETADATA_H
#define PLEXDRIVE_VIDEOMEDIAMETADATA_H

#include "document.h"

using namespace std;

class VideoMediaMetadata {
public:
    int width;
    int height;
    long durationMillis;

    VideoMediaMetadata();
    VideoMediaMetadata(rapidjson::Document &document);
};


#endif //PLEXDRIVE_VIDEOMEDIAMETADATA_H
