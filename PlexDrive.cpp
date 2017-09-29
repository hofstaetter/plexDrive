//
// Created by Matthias Hofstätter on 12.09.17.
//

#include <iostream>
#include <string>
#include <cerrno>
#include <vector>
#include <files/FilesApi.h>
#include "PlexDrive.h"
#include "GoogleDrive.h"

static struct fuse_operations operations = {
        .init = PlexDrive::init,
        .getattr = PlexDrive::getAttr,
        .readdir = PlexDrive::readDir,
        .open = PlexDrive::open,
        .read = PlexDrive::read,
};

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    return fuse_main(argc, argv, &operations, NULL);
}


int PlexDrive::VERBOSE = 0;

void *PlexDrive::init(struct fuse_conn_info *conn) {
    cout << "pleXDrive v0.0.1 | Frezy Software Studios" << endl;
    PlexDrive::VERBOSE = 1;
    GoogleDrive::init();
    return nullptr;
}

int PlexDrive::getAttr(const char *path, struct stat *stbuf) {
    cout << "[VERBOSE] getAddr " << path << endl;

    memset(stbuf, 0, sizeof(struct stat));

    try{
        File f = GoogleDrive::getFile(path);

        stbuf->st_mode = (f.getMimeType().compare("application/vnd.google-apps.folder") == 0) ? S_IFDIR | 0755 : S_IFREG | 0777;
        stbuf->st_nlink = 2;
        stbuf->st_size = f.getSize();
        //TODO modifiedTimes
        cout << "[VERBOSE] getAddr returns 0" << endl;
        return 0;
    } catch (int e) {
        cout << "[VERBOSE] getAddr returns -ENOENT" << endl;
        return -ENOENT;
    }
}

int PlexDrive::readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    cout << "[VERBOSE] readDir " << path << endl;

    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    vector<File> fv;

    try {
        fv = GoogleDrive::getDirectory(path);

        for(File f : fv) {
            filler(buf, f.getName().c_str(), NULL, 0);
        }
    } catch (int i) {

    }

    cout << "[VERBOSE] readDir returns 0" << endl;
    return 0;
}

int PlexDrive::open(const char *path, struct fuse_file_info *fi) {
    return 0;
}

int PlexDrive::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    cout << "[VERBOSE] read " << path << endl;

    if (strcmp(path, "/test") == 0) {
        size_t len = strlen("test");
        if (offset >= len) {
            cout << "[VERBOSE] returns 0" << endl;
            return 0;
        }

        if (offset + size > len) {
            memcpy(buf, "test" + offset, len - offset);
            cout << "[VERBOSE] returns " << len - offset << endl;
            return len - offset;
        }

        memcpy(buf, "test" + offset, size);
        cout << "[VERBOSE] returns " << size << endl;
        return size;
    }

    cout << "[VERBOSE] returns -ENOENT" << endl;
    return -ENOENT;
}
