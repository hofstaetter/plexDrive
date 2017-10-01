//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVEAPI_H
#define PLEXDRIVE_GOOGLEDRIVEAPI_H

#include <string>

using namespace std;

class GoogleDriveApi {
public:
    static int VERBOSE;
    static string PATH;
    static string CONFIG_PATH;

    static void init(int verbose = 0, string config = ".");

    static void download(string fileId);
};


#endif //PLEXDRIVE_GOOGLEDRIVEAPI_H
