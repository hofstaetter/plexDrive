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
    static time_t toEpoch(string time) {
        struct tm *tm;
        sscanf(time, "%i-%i-%iT%i:%i:%i", tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        return mktime(tm);
    }

    static string fromEpoch(time_t time) {
        struct tm *t = gmtime(&time);
        string buffer;
        strftime(buffer, 24, "%FT%X.000Z", t);
        return buffer;
    }
};


#endif //PLEXDRIVE_DATETIME_H
