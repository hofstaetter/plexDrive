//
// Created by Matthias Hofstätter on 29.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVECACHE_H
#define PLEXDRIVE_GOOGLEDRIVECACHE_H

#include <string>
#include <map>
#include <files/File.h>
#include <sqlite3.h>

using namespace std;

class GoogleDriveCache {
public:
    static void init(string path);
    static void insert(File f);
    static void remove(string fileId);
    static File &get(string fileId);

    static vector<string> getChildren(string fileId);
private:
    static string Path;
    static void prepareDb();
};


#endif //PLEXDRIVE_GOOGLEDRIVECACHE_H
