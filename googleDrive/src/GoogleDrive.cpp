//
// Created by Matthias Hofstätter on 19.09.17.
//

#include <changes/Change.h>
#include <changes/ChangesApi.h>
#include <files/File.h>
#include <files/FilesApi.h>
#include <fstream>
#include <thread>
#include "GoogleDrive.h"
#include "../GoogleDriveCache.h"

#include <files/FilesApi.h>
#include <GoogleDriveApi.h>

int GoogleDrive::VERBOSE;
string GoogleDrive::PATH;

File GoogleDrive::root;
string GoogleDrive::pageToken;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> splitPath(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

File GoogleDrive::getFile(string path) {
    File current = GoogleDrive::root;
    if(path == "/") return current; //if root

    start:
    string folder;
    path = path.substr(1, path.length());
    folder = path.substr(0, path.find("/"));
    if(path.find("/") != string::npos) {
        path = path.substr(path.find("/"), path.length());
    }

    for(string s : GoogleDriveCache::getChildren(current.getId())) {
        if(GoogleDriveCache::get(s).getName() == folder) {
            if(path.find("/") == string::npos)
                return GoogleDriveCache::get(s);
            current = GoogleDriveCache::get(s);
            goto start;
        }
    }

    throw -1;
}

vector<File> GoogleDrive::getDirectory(string path) {
    vector<File> result;

    vector<string> temp = GoogleDriveCache::getChildren(getFile(path).getId());

    for(string s : GoogleDriveCache::getChildren(getFile(path).getId())) {
        File f = GoogleDriveCache::get(s);
        result.push_back(f);
    }

    return result;
}

void GoogleDrive::init(int verbose, string path) {
    //cout << "GoogleDrive v0.0.1 | Frezy Software Studios";
    GoogleDrive::VERBOSE = verbose;
    GoogleDrive::PATH = path;

    GoogleDriveCache::init();

    GoogleDriveApi::init();

    GoogleDrive::root = FilesApi::get("root");

    GoogleDrive::getChanges();
}

void GoogleDrive::getChanges() {
    cout << "[VERBOSE] Updating cache..." << endl;
    if(GoogleDrive::pageToken.empty()) {
        GoogleDrive::pageToken = "1";
        rapidjson::Document configuration(rapidjson::kObjectType);
        ifstream file("googleDrive.json");
        if (file.is_open()) {
            string configurationstring;
            file >> configurationstring;
            file.close();

            configuration.Parse(configurationstring.c_str());
            if (configuration.IsObject()) {
                if (configuration.HasMember("nextPageToken"))
                    GoogleDrive::pageToken = configuration["nextPageToken"].GetString();
            }
        }
    }

    if(ChangesApi::getStartPageToken().getStartPageToken().c_str() == GoogleDrive::pageToken) {
        cout << "[VERBOSE] Cache already up to date." << endl;
        return;
    }

    long end = atol(ChangesApi::getStartPageToken().getStartPageToken().c_str());

    ChangeList cl;
    cl.setNextPageToken(GoogleDrive::pageToken);
    while(!cl.getNextPageToken().empty()) {
        //chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        cout << "[VERBOSE] Getting changes with page token " << cl.getNextPageToken() << "..." << endl;

        cl = ChangesApi::list(cl.getNextPageToken(), false, true, false, 1000, false, "", false, "", "", "nextPageToken,newStartPageToken,changes/removed,changes/file/id,changes/file/name,changes/file/mimeType,changes/file/size,changes/file/parents", false); /*changes/file/viewedByMeTime,changes/file/modifiedTime,*/

        //chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        for(Change &c : cl.getChanges()) {
            if(c.isRemoved()) {
                GoogleDriveCache::remove(c.getFile().getId());
            } else {
                File f = c.getFile();
                GoogleDriveCache::insert(f);
            }
        }

        cout << "[VERBOSE] Updated " << cl.getChanges().size() << " items." << endl;

        rapidjson::Document configuration(rapidjson::kObjectType);
        if(cl.getNextPageToken().empty())
            configuration.AddMember(rapidjson::StringRef("nextPageToken"), rapidjson::StringRef(cl.getNewStartPageToken().c_str()), configuration.GetAllocator());
        else
            configuration.AddMember(rapidjson::StringRef("nextPageToken"), rapidjson::StringRef(cl.getNextPageToken().c_str()), configuration.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        configuration.Accept(writer);

        string configurationstring = buffer.GetString();
        ofstream file("googleDrive.json");
        file << configurationstring;
        file.close();

        /*chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> d1 = t2 - t1;
        chrono::duration<double, milli> d2 = t3 - t2;
        cout << "Request: " << d1.count() << " ms | Fetch: " << d2.count() << " ms | Done: " << (atol(cl.getNextPageToken().c_str()) / end) << "%" << endl;*/
    }
    GoogleDrive::pageToken = cl.getNewStartPageToken();
}

void GoogleDrive::downloadFile(string path) {
    File f = GoogleDrive::getFile(path);

    thread t(GoogleDriveApi::download, f.getId());

    t.join();
}
