//
// Created by Matthias Hofstätter on 17.09.17.
//

#include "files/Thumbnail.h"

char Thumbnail::getImage() {
    return image;
}

void Thumbnail::setImage(char image) {
    Thumbnail::image = image;
}

string &Thumbnail::getMimeType() {
    return mimeType;
}

void Thumbnail::setMimeType(string &mimeType) {
    Thumbnail::mimeType = mimeType;
}
