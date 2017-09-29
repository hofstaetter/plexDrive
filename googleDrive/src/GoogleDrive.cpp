//
// Created by Matthias Hofstätter on 19.09.17.
//

#include <changes/Change.h>
#include <changes/ChangesApi.h>
#include <files/File.h>
#include <fstream>
#include <thread>
#include "GoogleDrive.h"
#include "../GoogleDriveCache.h"

#include <files/FilesApi.h>

int GoogleDrive::VERBOSE = 0;

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
    vector<string> folders = splitPath(path, '/');
    folders = vector<string>(folders.begin() + 1, folders.end());

    for(string i : folders) {
        for(string j : current.getParents()) {
            if((current = GoogleDriveCache::get(j)).getName() == i) {
                break;
            }
        }
    }

    vector<string> p = current.getParents();
    current.setParents(p);

    return current;
    /*if(path.empty()) throw -1;
    if(fileCache.size() < 1)
        fileCache.insert(make_pair("/", Files::get("root", false, false, false, "*")));
    if(path == "/") return fileCache.at("/");

    File f = googleDrive::fileCache.at("/");

    vector<string> folders = splitPath(path, '/');
    folders = vector<string>(folders.begin() + 1, folders.end());
    //get nearest known folder/File
    for(int i = folders.size(); i > 0; i--) {
        try {
            string subpath = "";
            for(int j = 0; j < i; j++) {
                subpath.append("/").append(folders[j]);
            }
            f = fileCache.at(subpath);
            folders = vector<string>(folders.begin() + i, folders.end());
            break;
        } catch (out_of_range &e) {
            continue;
        }
    }

    //get needed folders
    FileList fl;
    for(int i = 0; i < folders.size(); i++) {
        fl = Files::list("", "", "", "", 1, "", (i != folders.size() - 1) ? string("'").append(f.getId()).append("' in parents and name='").append(folders[i]).append("'+and+mimeType+=+'application/vnd.google-apps.folder'") :
                                                string("'").append(f.getId()).append("' in parents and name='").append(folders[folders.size() - 1]).append("'"));
        vector<File> fv = fl.getFiles();
        if(fv.size() > 0)
            f = fv[0];
        else
            throw -1;
    }

    googleDrive::fileCache[path] = f;

    return f;*/
    return File();
}

vector<File> GoogleDrive::getDirectory(string path) {
    vector<File> result;

    for(string s : GoogleDriveCache::getChildren(getFile(path).getId())) {
        result.push_back(GoogleDriveCache::get(s));
    }

    return result;
}

void GoogleDrive::init() {
    //cout << "GoogleDrive v0.0.1 | Frezy Software Studios";
    GoogleDriveCache::init("/Users/matthias/cache.sqlite");

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

        cl = ChangesApi::list(cl.getNextPageToken(), false, true, false, 1000, false, "", false, "", "", "nextPageToken,newStartPageToken,changes/removed,changes/file/id,changes/file/name,changes/file/mimeType,changes/file/webContentLink,changes/file/modifiedTime,changes/file/size,changes/file/parents", false);

        //chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        for(Change c : cl.getChanges()) {
            if(c.isRemoved()) {
                GoogleDriveCache::remove(c.getFile().getId());
            } else {
                GoogleDriveCache::insert(c.getFile());
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
