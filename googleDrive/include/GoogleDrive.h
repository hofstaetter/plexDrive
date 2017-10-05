//
// Created by Matthias Hofstätter on 21.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVE_H
#define PLEXDRIVE_GOOGLEDRIVE_H

#include <exception>
#include <chrono>
#include <sqlite3.h>
#include <fstream>
#include <thread>
#include <future>
#include <sys/stat.h>

#include <files/File.h>
#include <changes/Change.h>
#include <changes/ChangesApi.h>
#include <files/File.h>
#include <files/FilesApi.h>
#include "../FileCache.h"
#include <../ChunkCache.h>
#include <files/FilesApi.h>
#include <GoogleDriveApi.h>
#include <Response.h>

extern string GOOGLEDRIVE_PATH;
extern string GOOGLEDRIVE_CONFIG;
extern int GOOGLEDRIVE_VERBOSE;

class GoogleDrive {
private:
    static File root;
    static string pageToken;
    static long long int updateTimestamp;

    static void getChanges();
public:
    static void init(int verbose = 0, string path = ".");

    static File getFile(string path);
    static int readFile(File file, char *buf, size_t size, off_t offset);

    static vector<File> readDirectory(File file);
    static void createDirectory(string path);
};


#endif //PLEXDRIVE_GOOGLEDRIVE_H
