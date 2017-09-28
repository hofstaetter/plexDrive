//
// Created by Matthias Hofstätter on 21.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVE_H
#define PLEXDRIVE_GOOGLEDRIVE_H

#include <files/File.h>
#include <sqlite3.h>

class googleDrive {
private:
    static File root;
    static string pageToken;
    static void insertIntoCache(File f);
    static void deleteFromCache(string fileId);
    static File getFromCache(string fileId);
    static vector<string> getParents(string fileId);
    static vector<string> getChildren(string fileId);
    static void workOffChanges();
    static void initCache();
public:
    static File getFile(string path);
    static vector<File> getDirectory(string path);
    static void init();
};


#endif //PLEXDRIVE_GOOGLEDRIVE_H
