//
// Created by Matthias Hofstätter on 29.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVECACHE_H
#define PLEXDRIVE_GOOGLEDRIVECACHE_H

#include <string>
#include <map>
#include <exception>
#include <mutex>
#include <sqlite3.h>
#include <files/File.h>
#include <GoogleDrive.h>

using namespace std;

class FileCache {
public:
    static void init();
    static void insert(File f);
    static void remove(string fileId);
    static File get(string fileId);

    static vector<string> getChildren(string fileId);
private:
    static std::mutex DATABASE_MUTEX;

    static void prepareDb();
    static sqlite3 *openDb();
    static void closeDb(sqlite3 *db);
};


#endif //PLEXDRIVE_GOOGLEDRIVECACHE_H
