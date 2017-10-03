//
// Created by Matthias Hofstätter on 12.09.17.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <cerrno>
#include <vector>
#include <files/FilesApi.h>
#include <fstream>
#include <thread>
#include "PlexDrive.h"
#include "GoogleDrive.h"

using namespace std;

string PlexDrive::PATH = ".";

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
    //cout << "[VERBOSE] getAddr " << path << endl;

    memset(stbuf, 0, sizeof(struct stat));

    try{
        File f = GoogleDrive::getFile(path);

        stbuf->st_mode = (f.getMimeType() == "application/vnd.google-apps.folder") ? S_IFDIR | 0755 : S_IFREG | 0777;
        stbuf->st_nlink = (f.getMimeType() == "application/vnd.google-apps.folder") ? 2 : 1;
        stbuf->st_size = (f.getMimeType() == "application/vnd.google-apps.folder") ? 0 : f.getSize();
        //TODO modifiedTimes
        //cout << "[VERBOSE] getAddr returns 0" << endl;
        return 0;
    } catch (int e) {
        //cout << "[VERBOSE] getAddr returns -ENOENT" << endl;
        return -ENOENT;
    }
}

int PlexDrive::readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    //cout << "[VERBOSE] readDir " << path << endl;

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

    //cout << "[VERBOSE] readDir returns 0" << endl;
    return 0;
}

int PlexDrive::open(const char *path, struct fuse_file_info *fi) {
    cout << "[VERBOSE] open " << path << endl;
    try {
        File file = GoogleDrive::getFile(path);

        /*FILE *file = fopen((PlexDrive::PATH + "/" + f.getId()).c_str(), "r");
        if(!file) {
            GoogleDrive::downloadFile(path);
        } else {
            fseek(file, 0, SEEK_END);
            if (ftell(file) != f.getSize()) {
                if (file) remove(f.getId().c_str());
                GoogleDrive::downloadFile(path);
            }
        }*/
    } catch (int i) {
        return -ENOENT;
    }
    //TODO access rights

    return 0;
}

int PlexDrive::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    //cout << "[VERBOSE] read " << path << endl;

    File file = GoogleDrive::getFile(path);
    GoogleDrive::downloadFile(path);

    if(offset >= file.getSize())
        return 0;

    struct stat statbuffer;
    int statResult;
    statResult = stat(file.getId().c_str(), &statbuffer);
    while(statResult != 0 || offset + size > statbuffer.st_size) {
        //cout << "Waiting for file " << offset + size << ">" << statbuffer.st_size << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
        statResult = stat(file.getId().c_str(), &statbuffer);
    }

    ifstream filestream;
    if(offset + size > file.getSize()) {
        filestream.open(file.getId().c_str(), ios::in || ios::binary);
        filestream.seekg(offset, filestream.beg);
        filestream.read(buf, size);
        filestream.close();
        return file.getSize() - offset;
    }

    filestream.open(file.getId().c_str(), ios::in || ios::binary);
    filestream.seekg(offset, filestream.beg);
    filestream.read(buf, size);
    filestream.close();
    return size;


    /*cout << "[VERBOSE] returns -ENOENT" << endl;
    return -ENOENT;*/
}
