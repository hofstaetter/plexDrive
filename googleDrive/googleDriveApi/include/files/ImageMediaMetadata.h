//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_IMAGEMEDIAMETADATA_H
#define PLEXDRIVE_IMAGEMEDIAMETADATA_H


#include "Location.h"
#include "document.h"
#include <string>

using namespace std;

class ImageMediaMetadata {
public:
    int width;
    int height;
    int rotation;
    Location location;
    std::string time;
    std::string cameraMake;
    std::string cameraModel;
    float exposureTime;
    float aperture;
    bool flashUsed;
    float focalLength;
    int isoSpeed;
    std::string meteringMode;
    std::string sensor;
    std::string exposureMode;
    std::string colorSpace;
    std::string whiteBalance;
    float exposureBias;
    float maxApertureValue;
    int subjectDistance;
    std::string lens;

    ImageMediaMetadata();
    ImageMediaMetadata(rapidjson::Document &document);
};


#endif //PLEXDRIVE_IMAGEMEDIAMETADATA_H
