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

    cout << "[DEBUG] PLEXDRIVE_VERBOSE = " << PLEXDRIVE_VERBOSE << endl;
    cout << "[DEBUG] PLEXDRIVE_PATH = " << PLEXDRIVE_PATH << endl;
    GoogleDrive::init(PLEXDRIVE_VERBOSE, PLEXDRIVE_PATH);

    return nullptr;
}

int PlexDrive::getAttr(const char *path, struct stat *stbuf) {
    cout << "[DEBUG] PlexDrive::getAttr(" << path << ")" << endl;

    memset(stbuf, 0, sizeof(struct stat));

    try{
        File f = GoogleDrive::getFile(path);

        stbuf->st_mode = (f.getMimeType() == "application/vnd.google-apps.folder") ? S_IFDIR | 0755 : S_IFREG | 0777;
        stbuf->st_nlink = (f.getMimeType() == "application/vnd.google-apps.folder") ? 2 : 1;
        stbuf->st_size = (f.getMimeType() == "application/vnd.google-apps.folder") ? 0 : f.getSize();
        //TODO modifiedTimes

        cout << "[DEBUG] PlexDrive::getAttr(" << path << ") returns " << 0 << endl;

        return 0;
    } catch (int e) {
        return -ENOENT;
    }
}

int PlexDrive::readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    cout << "[DEBUG] PlexDrive::readDir(" << path << ")" << endl;
    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    cout << "[DEBUG] PlexDrive::readDir(" << path << ") added " << "." << endl;
    filler(buf, "..", NULL, 0);
    cout << "[DEBUG] PlexDrive::readDir(" << path << ") added " << ".." << endl;

    vector<File> fv;

    try {
        File file = GoogleDrive::getFile(path);
        cout << "[DEBUG] PlexDrive::readDir(" << path << ") got " << file.getName() << endl;
        fv = GoogleDrive::readDirectory(file);
        cout << "[DEBUG] PlexDrive::readDir(" << path << ") got directory from cache" << endl;

        for(File f : fv) {
            filler(buf, f.getName().c_str(), NULL, 0);
            cout << "[DEBUG] PlexDrive::readDir(" << path << ") added " << f.getName() << endl;
        }
    } catch (int i) {
        throw exception();
    }

    cout << "[DEBUG] PlexDrive::readDir(" << path << ") returns " << 0 << endl;

    return 0;
}

int PlexDrive::open(const char *path, struct fuse_file_info *fi) {
    cout << "[DEBUG] PlexDrive::open(" << path << ")" << endl;
    try {
        //File file = GoogleDrive::getFile(path);
        //TODO check online status here?
    } catch (int i) {
        cout << "[DEBUG] PlexDrive::open(" << path << ") returns " << "-ENOENT" << endl;
        return -ENOENT;
    }
    //TODO access rights

    cout << "[DEBUG] PlexDrive::open(" << path << ") returns " << 0 << endl;

    return 0;
}

int PlexDrive::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    cout << "[DEBUG] PlexDrive::read(" << path << ", " << size << ", " << offset << ")" << endl;

    File file = GoogleDrive::getFile(path);
    cout << "[DEBUG] PlexDrive::read(" << path << ", " << size << ", " << offset << ") got file " << file.getName() << endl;

    if(offset >= file.getSize())
        return 0;

    int count = GoogleDrive::readFile(file, buf, size, offset);
    cout << "[DEBUG] PlexDrive::read(" << path << ", " << size << ", " << offset << ") read " << count << " bytes from " << file.getName() << endl;

    cout << "[DEBUG] PlexDrive::read(" << path << ", " << size << ", " << offset << ") returns " << 0 << endl;

    return count;
}

int PlexDrive::mkdir(const char *path, mode_t mode) {
    GoogleDrive::createDirectory(path);

    return 0;
}
