//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVEAPI_H
#define PLEXDRIVE_GOOGLEDRIVEAPI_H

#include <string>
#include "Response.h"
#include "files/File.h"

using namespace std;

extern int VERBOSE;
extern string PATH;
extern string CONFIG_PATH;

class GoogleDriveApi {
public:
    static void init(int verbose = 0, string config = ".");

    static Response download(string fileId, long from, long to);
};


#endif //PLEXDRIVE_GOOGLEDRIVEAPI_H
