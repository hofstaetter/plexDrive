//
// Created by Matthias Hofstätter on 12.09.17.
//

#ifndef PLEXDRIVE_PLEXDRIVE_H
#define PLEXDRIVE_PLEXDRIVE_H

#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <boost/log/trivial.hpp>
#include "GoogleDrive.h"

class PlexDrive {
private:
    static int VERBOSE;
    static string PATH;

    static GoogleDrive gD;
public:
    static void *init(struct fuse_conn_info *conn);
    static int getAttr(const char *path, struct stat *stbuf);
    static int readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
    static int open(const char *path, struct fuse_file_info *fi);
    static int read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
    static int mkdir(const char* path, mode_t mode);
};


#endif //PLEXDRIVE_PLEXDRIVE_H
