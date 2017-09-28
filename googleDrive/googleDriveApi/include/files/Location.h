//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_LOCATION_H
#define PLEXDRIVE_LOCATION_H


class Location {
private:
    double latitude;
    double longitude;
    double altitude;
public:
    Location();
    Location(rapidjson::Document &document);

    double getLatitude();
    void setLatitude(double latitude);

    double getLongitude();
    void setLongitude(double longitude);

    double getAltitude();
    void setAltitude(double altitude);
};


#endif //PLEXDRIVE_LOCATION_H
