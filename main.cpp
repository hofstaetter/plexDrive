#include <iostream>
#include <oauth/GoogleOAuth.h>

#include "plexDrive.h"

static struct fuse_operations operations;

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    operations.init = plexDrive::init;
    operations.getattr = plexDrive::getAttr;
    operations.readdir = plexDrive::readDir;
    operations.open = plexDrive::open;
    operations.read = plexDrive::read;

    return fuse_main(argc, argv, &operations, NULL);
}