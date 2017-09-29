//
// Created by Matthias Hofstätter on 21.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVE_H
#define PLEXDRIVE_GOOGLEDRIVE_H

#include <files/File.h>
#include <sqlite3.h>
#include <boost/log/trivial.hpp>

class GoogleDrive {
private:
    static int VERBOSE;

    static File root;
    static string pageToken;
    static void workOffChanges();
public:
    static File getFile(string path);
    static vector<File> getDirectory(string path);
    static void init();
};


#endif //PLEXDRIVE_GOOGLEDRIVE_H
