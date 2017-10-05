//
// Created by Matthias Hofstätter on 12.09.17.
//


#include "PlexDrive.h"

using namespace std;

int PLEXDRIVE_VERBOSE = 0;
string PLEXDRIVE_PATH = ".";
string PLEXDRIVE_MOUNT = ".";

static struct fuse_operations operations;

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    operations.init = PlexDrive::init;
    operations.getattr = PlexDrive::getAttr;
    operations.readdir = PlexDrive::readDir;
    operations.open = PlexDrive::open;
    operations.read = PlexDrive::read;
    operations.mkdir = PlexDrive::mkdir;

    for(int i = 0; i < argc; i++) {
        if(strcmp("-c", argv[i]) == 0) {
            PLEXDRIVE_PATH = argv[i + 1];
            argc -= 2;
        }
    }

    return fuse_main(argc, argv, &operations, NULL);
}



void *PlexDrive::init(struct fuse_conn_info *conn) {
    cout << "PlexDrive | Frezy Software Studios | @copy Matthias Hofstätter" << endl;

    PLEXDRIVE_VERBOSE = 1;

    GoogleDrive::init(PLEXDRIVE_VERBOSE, PLEXDRIVE_PATH);

    return nullptr;
}

int PlexDrive::getAttr(const char *path, struct stat *stbuf) {
    //cout << "[VERBOSE] getAttr " << path << endl;

    memset(stbuf, 0, sizeof(struct stat));

    try{
        File f = GoogleDrive::getFile(path);

        stbuf->st_mode = (f.getMimeType() == "application/vnd.google-apps.folder") ? S_IFDIR | 0755 : S_IFREG | 0777;
        stbuf->st_nlink = (f.getMimeType() == "application/vnd.google-apps.folder") ? 2 : 1;
        stbuf->st_size = (f.getMimeType() == "application/vnd.google-apps.folder") ? 0 : f.getSize();
        //TODO modifiedTimes
        return 0;
    } catch (int e) {
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
        File file = GoogleDrive::getFile(path);
        fv = GoogleDrive::readDirectory(file);


        for(File f : fv) {
            filler(buf, f.getName().c_str(), NULL, 0);
        }
    } catch (int i) {

    }

    return 0;
}

int PlexDrive::open(const char *path, struct fuse_file_info *fi) {
    //cout << "[VERBOSE] open " << path << endl;
    try {
        //File file = GoogleDrive::getFile(path);
        //TODO check online status here?
    } catch (int i) {
        return -ENOENT;
    }
    //TODO access rights

    return 0;
}

int PlexDrive::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    //cout << "[VERBOSE] read " << path << " from " << offset << " to " << offset + size << endl;

    File file = GoogleDrive::getFile(path);

    if(offset >= file.getSize())
        return 0;

    int count = GoogleDrive::readFile(file, buf, size, offset);

    return count;

    /*struct stat statbuffer;
    int statResult;
    statResult = stat(file.getId().c_str(), &statbuffer);
    while(statResult != 0 || offset + size > statbuffer.st_size) {
        //cout << "Waiting for file " << offset + size << ">" << statbuffer.st_size << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
        statResult = stat(file.getId().c_str(), &statbuffer);
    }

    cout << "[VERBOSE] read now " << path << " from " << offset << " to " << offset + size << endl;

    ifstream filestream;
    if(offset + size > file.getSize()) {
        filestream.open(file.getId().c_str(), ios::in | ios::binary);
        filestream.seekg(offset, filestream.beg);
        filestream.read(buf, size);
        filestream.close();
        return file.getSize() - offset;
    }

    filestream.open(file.getId().c_str(), ios::in | ios::binary);
    filestream.seekg(offset, filestream.beg);
    filestream.read(buf, size);
    filestream.close();
    return size;*/


    /*cout << "[VERBOSE] returns -ENOENT" << endl;
    return -ENOENT;*/
}

int PlexDrive::mkdir(const char *path, mode_t mode) {
    GoogleDrive::createDirectory(path);

    return 0;
}
