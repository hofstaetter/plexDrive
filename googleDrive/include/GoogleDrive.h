//
// Created by Matthias Hofstätter on 21.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVE_H
#define PLEXDRIVE_GOOGLEDRIVE_H

#include <files/File.h>
#include <sqlite3.h>
#include <boost/log/trivial.hpp>

extern long CHUNK_SIZE;

class GoogleDrive {
private:
    static File root;
    static string pageToken;
    static string cachePath;
    static string configPath;
    static vector<string> currentDownloads;

    static void getChanges();
public:
    static int VERBOSE;
    static string PATH;

    static void init(int verbose = 0, string path = ".");

    static File getFile(string path);
    static vector<File> getDirectory(string path);
    static void downloadFile(string path);
};


#endif //PLEXDRIVE_GOOGLEDRIVE_H
