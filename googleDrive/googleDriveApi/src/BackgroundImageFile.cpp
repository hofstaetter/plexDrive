//
// Created by Matthias Hofstätter on 17.09.17.
//

#include <teamdrives/BackgroundImageFile.h>

BackgroundImageFile::BackgroundImageFile() {
}

BackgroundImageFile::BackgroundImageFile(rapidjson::Document &document) {
    if(document.HasMember("id"))
        this->id = document["id"].GetString();
    if(document.HasMember("xCoordinate"))
        this->xCoordinate = document["xCoordinate"].GetFloat();
    if(document.HasMember("yCoordinate"))
        this->yCoordinate = document["yCoordinate"].GetFloat();
    if(document.HasMember("width"))
        this->width = document["width"].GetFloat();
}

string &BackgroundImageFile::getId() {
    return id;
}

void BackgroundImageFile::setId(string &id) {
    BackgroundImageFile::id = id;
}

float BackgroundImageFile::getXCoordinate() {
    return xCoordinate;
}

void BackgroundImageFile::setXCoordinate(float xCoordinate) {
    BackgroundImageFile::xCoordinate = xCoordinate;
}

float BackgroundImageFile::getYCoordinate() {
    return yCoordinate;
}

void BackgroundImageFile::setYCoordinate(float yCoordinate) {
    BackgroundImageFile::yCoordinate = yCoordinate;
}

float BackgroundImageFile::getWidth() {
    return width;
}

void BackgroundImageFile::setWidth(float width) {
    BackgroundImageFile::width = width;
}

/*string BackgroundImageFile::getId() {
    if(this->document->HasMember("id"))
        return this->getString("id");
    return "";
}

void BackgroundImageFile::setId(string id) {
    this->setString("id", id);
}

float BackgroundImageFile::getXCoordinate() {
    if(this->document->HasMember("xCoordinate"))
        return this->getFloat("xCoordinate");
    return 0.0f;
}

void BackgroundImageFile::setXCoordinate(float xCoordinate) {
    this->setFloat("xCoordinate", xCoordinate);
}

float BackgroundImageFile::getYCoordinate() {
    if(this->document->HasMember("yCoordinate"))
        return this->getFloat("yCoordinate");
    return 0.0f;
}

void BackgroundImageFile::setYCoordinate(float yCoordinate) {
    this->setFloat("yCoordinate", yCoordinate);
}

float BackgroundImageFile::getWidth() {
    if(this->document->HasMember("width"))
        return this->getFloat("width");
    return 0.0f;
}

void BackgroundImageFile::setWidth(float width) {
    this->setFloat("width", width);
}*/
