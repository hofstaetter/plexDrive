//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_DATETIME_H
#define PLEXDRIVE_DATETIME_H

#include <ctime>
#include <string>

using namespace std;

class DateTime {
public:
    static time_t toEpoch(string &time) {
        struct tm *tm;
        tm->tm_year = atoi(time.substr(0, 4).c_str());
        tm->tm_mon = atoi(time.substr(5, 2).c_str());
        tm->tm_mday = atoi(time.substr(8, 2).c_str());
        tm->tm_hour = atoi(time.substr(11,2).c_str());
        tm->tm_min = atoi(time.substr(14, 2).c_str());
        tm->tm_sec = atoi(time.substr(17, 2).c_str());
        //strptime(time.c_str(), "%Y-%m-%dT%H:%M:%S", &tm); //TODO
        //sscanf(time.c_str(), "%i-%i-%iT%i:%i:%i", &tm->tm_year, &tm->tm_mon, &tm->tm_mday, &tm->tm_hour, &tm->tm_min, &tm->tm_sec);
        return mktime(tm);
    }

    static string fromEpoch(time_t &time) {
        struct tm *t = gmtime(&time);
        char *buffer;
        strftime(buffer, 24, "%FT%X.000Z", t);
        return buffer;
    }
};


#endif //PLEXDRIVE_DATETIME_H
