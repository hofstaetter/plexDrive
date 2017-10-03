//
// Created by Matthias Hofstätter on 01.10.17.
//

#ifndef PLEXDRIVE_RESPONSE_H
#define PLEXDRIVE_RESPONSE_H

#include <string>

using namespace std;

class Response {
public:
    string header;
    string body;
    long httpStatusCode;

    Response();
};


#endif //PLEXDRIVE_RESPONSE_H
