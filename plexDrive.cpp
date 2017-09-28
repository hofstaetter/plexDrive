//
// Created by Matthias Hofstätter on 12.09.17.
//

#include <string>
#include <cerrno>
#include <vector>
#include <files/Files.h>
#include "plexDrive.h"
#include "googleDrive.h"


void *plexDrive::init(struct fuse_conn_info *conn) {
    googleDrive::init();
    return nullptr;
}

int plexDrive::getAttr(const char *path, struct stat *stbuf) {
    printf("getAddr(%s)\n", path);

    memset(stbuf, 0, sizeof(struct stat));

    try{
        File f = googleDrive::getFile(path);

        stbuf->st_mode = (f.getMimeType().compare("application/vnd.google-apps.folder") == 0) ? S_IFDIR | 0755 : S_IFREG | 0777;
        stbuf->st_nlink = 1;
        stbuf->st_size = f.getSize();
        return 0;
    } catch (int e) {
        return -ENOENT;
    }
}

int plexDrive::readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    printf("readDir(%s)\n", path);

    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    vector<File> fv;

    try {
        fv = googleDrive::getDirectory(path);

        for(File f : fv) {
            filler(buf, f.getName().c_str(), NULL, 0);
        }
    } catch (int i) {

    }

    return 0;
}

int plexDrive::open(const char *path, struct fuse_file_info *fi) {
    return 0;
}

int plexDrive::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    printf("read(%s)\n", path);

    if (strcmp(path, "/test") == 0) {
        size_t len = strlen("test");
        if (offset >= len) {
            return 0;
        }

        if (offset + size > len) {
            memcpy(buf, "test" + offset, len - offset);
            return len - offset;
        }

        memcpy(buf, "test" + offset, size);
        return size;
    }

    return -ENOENT;
}
