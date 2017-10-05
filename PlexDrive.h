//
// Created by Matthias Hofstätter on 12.09.17.
//

#ifndef PLEXDRIVE_PLEXDRIVE_H
#define PLEXDRIVE_PLEXDRIVE_H

#define FUSE_USE_VERSION 32

#include <iostream>
#include <cstdio>
#include <string>
#include <cerrno>
#include <vector>
#include <files/FilesApi.h>
#include <fstream>
#include <thread>
#include <thread>
#include <fuse.h>
#include <boost/log/trivial.hpp>

#include "GoogleDrive.h"
#include "PlexDrive.h"
#include "GoogleDrive.h"

extern int PLEXDRIVE_VERBOSE;
extern string PLEXDRIVE_PATH;
extern string PLEXDRIVE_MOUNT;

class PlexDrive {
public:
    static void *init(struct fuse_conn_info *conn);
    static int getAttr(const char *path, struct stat *stbuf);
    static int readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
    static int open(const char *path, struct fuse_file_info *fi);
    static int read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
    static int mkdir(const char* path, mode_t mode);
};


#endif //PLEXDRIVE_PLEXDRIVE_H
