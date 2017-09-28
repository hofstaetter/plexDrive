//
// Created by Matthias Hofstätter on 17.09.17.
//

#include <document.h>
#include "files/Location.h"

Location::Location() {

}

Location::Location(rapidjson::Document &document) {
    throw -1;
}

double Location::getLatitude() {
    return latitude;
}

void Location::setLatitude(double latitude) {
    Location::latitude = latitude;
}

double Location::getLongitude() {
    return longitude;
}

void Location::setLongitude(double longitude) {
    Location::longitude = longitude;
}

double Location::getAltitude() {
    return altitude;
}

void Location::setAltitude(double altitude) {
    Location::altitude = altitude;
}
