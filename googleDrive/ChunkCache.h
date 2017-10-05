//
// Created by Matthias Hofstätter on 05.10.17.
//

#ifndef PLEXDRIVE_CHUNKCACHE_H
#define PLEXDRIVE_CHUNKCACHE_H


#include <cstdlib>
#include <files/File.h>
#include <thread>

class ChunkCache {

    struct Download {
        File file;
        size_t size;
        off_t offset;
    };

private:
    static long CHUNK_SIZE;

    static std::vector<Download> downloadQueue;
    static std::mutex downloadQueueMutex;
    static std::vector<thread> downloads;
    static std::mutex downloadsMutex;

    static bool isChunk(File file, int part);

    static void download(File file, size_t size = SIZE_MAX, off_t offset = 0);
    static void downloadAsync(File file, size_t size = SIZE_MAX, off_t offset = 0);
public:
    static int read(File file, char *buf, size_t size, off_t offset);
};


#endif //PLEXDRIVE_CHUNKCACHE_H
