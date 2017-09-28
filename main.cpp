#include <iostream>
#include <oauth/googleOAuth.h>

#include "plexDrive.h"

static struct fuse_operations operations = {
        .init = plexDrive::init,
        .getattr = plexDrive::getAddr,
        .readdir = plexDrive::readDir,
        .open = plexDrive::open,
        .read = plexDrive::read,
};

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    return fuse_main(argc, argv, &operations, NULL);
}