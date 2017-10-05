//
// Created by Matthias Hofstätter on 05.10.17.
//

#include <sys/stat.h>
#include <future>
#include <GoogleDrive.h>
#include "ChunkCache.h"

long ChunkCache::CHUNK_SIZE = 10485760;

int ChunkCache::read(File file, char *buf, size_t size, off_t offset) {
    cout << "[DEBUG] ChunkCache::read(" << file.getId() << ", " << size << ", " << offset << ")" << endl;
    if(offset > file.getSize() || size == 0)
        return 0;

    if(offset + size > file.getSize())
        size = file.getSize() - offset;

    //download parts not local
    for(int i = offset / ChunkCache::CHUNK_SIZE; i <= (offset + size - 1) / ChunkCache::CHUNK_SIZE; i++) {
        ChunkCache::downloadAsync(file, ChunkCache::CHUNK_SIZE * 4, ChunkCache::CHUNK_SIZE * i);
    }

    int bytesWritten = 0;
    //write to result if available
    for(int i = offset / ChunkCache::CHUNK_SIZE; i <= (offset + size - 1) / ChunkCache::CHUNK_SIZE; i++) {
        struct stat statbuffer;
        int statResult = stat((GOOGLEDRIVE_PATH + "/" + file.getId() + "." + to_string(i)).c_str(), &statbuffer);
        while(statResult != 0 || !(statbuffer.st_size == ChunkCache::CHUNK_SIZE || statbuffer.st_size == file.getSize() % ChunkCache::CHUNK_SIZE)) { //TODO
            statResult = stat((GOOGLEDRIVE_PATH + "/" + file.getId() + "." + to_string(i)).c_str(), &statbuffer);
        }

        cout << "[DEBUG] " << file.getId() << "." << i << " ready for reading" << endl;

        ifstream filestream;
        filestream.open((GOOGLEDRIVE_PATH + "/" + file.getId() + "." + to_string(i)).c_str(), ios::in | ios::binary);
        if(filestream.is_open()) {
            if(i == offset / ChunkCache::CHUNK_SIZE && i == (offset + size - 1) / ChunkCache::CHUNK_SIZE) { //single chunk
                filestream.seekg(offset % ChunkCache::CHUNK_SIZE, filestream.beg);
                filestream.read(buf + bytesWritten, size);
                bytesWritten += size;
            } else if(i == offset / ChunkCache::CHUNK_SIZE) { //first chunk from multiple
                filestream.seekg(offset % ChunkCache::CHUNK_SIZE, filestream.beg);
                filestream.read(buf + bytesWritten, ChunkCache::CHUNK_SIZE - (offset % ChunkCache::CHUNK_SIZE));
                bytesWritten += ChunkCache::CHUNK_SIZE - (offset % ChunkCache::CHUNK_SIZE);
            } else if(i == (offset + size - 1) / ChunkCache::CHUNK_SIZE) { //last chunk forum multiple
                filestream.read(buf + bytesWritten, ChunkCache::CHUNK_SIZE - ((offset + size) % ChunkCache::CHUNK_SIZE));
                bytesWritten += ChunkCache::CHUNK_SIZE - ((offset + size) % ChunkCache::CHUNK_SIZE);
            } else { //chunk in the middle of multiple chunks
                filestream.read(buf + bytesWritten, ChunkCache::CHUNK_SIZE);
                bytesWritten += ChunkCache::CHUNK_SIZE;
            }
        } else { throw exception(); }
        filestream.close();
    }

    cout << "[DEBUG] ChunkCache::read(" << file.getId() << ", " << size << ", " << offset << ") returns " << size << endl;

    return size;
}

void ChunkCache::download(File file, size_t size, off_t offset) {
    cout << "[DEBUG] ChunkCache::download(" << file.getId() << ", " << size << ", " << offset << ")" << endl;
    if(offset > file.getSize() || size == 0) return;

    if(offset + size > file.getSize()) size = file.getSize() - offset;
    if(size == SIZE_MAX) size = file.getSize();

    //map chunkNumber result
    map<long, future<Response>> threads;
    ofstream filestream;

    //start required chunks
    for(int i = offset / ChunkCache::CHUNK_SIZE; i <= (offset + size - 1) / ChunkCache::CHUNK_SIZE; )
    {
        for(; i <= (offset + size - 1) / ChunkCache::CHUNK_SIZE && threads.size() <= 4; i++) {
            if(isChunk(file, i)) { //already downloading or downloaded
                continue;
            }

            filestream.open((GOOGLEDRIVE_PATH + "/" + file.getId() + "." + to_string(i)).c_str(), ios::out | ios::binary);
            if(!filestream.is_open()) {
                throw exception();
            }
            filestream.close();

            cout << "[VERBOSE] downloading " << file.getId() << "." << i << " from " << offset << " to " << offset + size << endl;

            threads.emplace(i, async(launch::async, GoogleDriveApi::download, file.getId(), i * CHUNK_SIZE, ((i + 1) * CHUNK_SIZE) - 1));
        }

        //collect all threads
        while(!threads.empty()) {
            for(map<long, future<Response>>::iterator iter = threads.begin(); iter != threads.end(); ++iter) {
                if(iter->second.wait_for(chrono::milliseconds(10)) == future_status::ready) {
                    filestream.open((GOOGLEDRIVE_PATH + "/" + file.getId() + "." + to_string(iter->first)).c_str(), ios::out | ios::binary);
                    if(filestream.is_open()) {
                        filestream << iter->second.get().body;
                    } else { throw exception(); }
                    filestream.close();

                    cout << "[VERBOSE] written " << file.getId() << "." << iter->first << endl;

                    threads.erase(iter);
                    break;
                }
            }
        }
    }
    cout << "[DEBUG] ChunkCache::download(" << file.getId() << ", " << size << ", " << offset << ") returns" << endl;
}

bool ChunkCache::isChunk(File file, int part) {
    struct stat statbuffer;
    int statResult = stat((GOOGLEDRIVE_PATH + "/" + file.getId() + "." + to_string(part)).c_str(), &statbuffer);
    if(statResult == 0) {
        return true;
    }

    return false;
}

void ChunkCache::downloadAsync(File file, size_t size, off_t offset) {
    thread t(ChunkCache::download, file, size, offset);
    t.detach();
}
