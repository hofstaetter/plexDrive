//
// Created by Matthias Hofstätter on 19.09.17.
//

#include "GoogleDrive.h"

string GOOGLEDRIVE_PATH;
string GOOGLEDRIVE_CONFIG;
int GOOGLEDRIVE_VERBOSE;

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

long long int GoogleDrive::updateTimestamp;

File GoogleDrive::getFile(string path) {
    long long int currentTimestamp = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
    if(updateTimestamp + 30000 < currentTimestamp) {
        getChanges();
    }

    File current = GoogleDrive::root;
    if(path == "/") return current; //if root

    start:
    string folder;
    path = path.substr(1, path.length());
    folder = path.substr(0, path.find("/"));
    if(path.find("/") != string::npos) {
        path = path.substr(path.find("/"), path.length());
    }

    for(string s : FileCache::getChildren(current.getId())) {
        if(FileCache::get(s).getName() == folder) {
            if(path.find("/") == string::npos) {
                return FileCache::get(s);
            }
            current = FileCache::get(s);
            goto start;
        }
    }

    throw -1;
}

vector<File> GoogleDrive::readDirectory(File file) {
    cout << "[DEBUG] GoogleDrive::readDirectory(" << file.getName() << ")" << endl;
    vector<File> result;

    vector<string> temp = FileCache::getChildren(file.getId());

    for(string s : FileCache::getChildren(file.getId())) {
        cout << "[DEBUG] GoogleDrive::readDirectory(" << file.getName() << ") add file with id " << s << endl;
        File f = FileCache::get(s);
        result.push_back(f);
        cout << "[DEBUG] GoogleDrive::readDirectory(" << file.getName() << ") added " << f.getName() << endl;
    }

    return result;
}

void GoogleDrive::init(int verbose, string path) {
    GOOGLEDRIVE_PATH = path;
    GOOGLEDRIVE_CONFIG = path + "/googleDrive.json";
    GOOGLEDRIVE_VERBOSE = verbose;

    FileCache::init();

    GoogleDriveApi::init(GOOGLEDRIVE_VERBOSE, GOOGLEDRIVE_PATH);

    GoogleDrive::root = FilesApi::get("root");

    GoogleDrive::getChanges();
}

void GoogleDrive::getChanges() {
    GoogleDrive::updateTimestamp = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();

    //cout << "[VERBOSE] Updating cache..." << endl;
    if(GoogleDrive::pageToken.empty()) {
        GoogleDrive::pageToken = "1";
        rapidjson::Document configuration(rapidjson::kObjectType);
        ifstream file(GOOGLEDRIVE_CONFIG);
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
        //cout << "[VERBOSE] Cache already up to date." << endl;
        return;
    }

    long end = atol(ChangesApi::getStartPageToken().getStartPageToken().c_str());

    ChangeList cl;
    cl.setNextPageToken(GoogleDrive::pageToken);
    while(!cl.getNextPageToken().empty()) {
        //chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        cout << "[VERBOSE] Getting changes with page token " << cl.getNextPageToken() << "..." << endl;

        cl = ChangesApi::list(cl.getNextPageToken(), false, true, false, 1000, false, "", false, "", "", "kind,nextPageToken,newStartPageToken,changes/kind,changes/removed,changes/file/kind,changes/file/id,changes/file/name,changes/file/mimeType,changes/file/size,changes/file/parents", false); /*changes/file/viewedByMeTime,changes/file/modifiedTime,*/

        //chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        for(Change &c : cl.getChanges()) {
            if(c.isRemoved()) {
                FileCache::remove(c.getFile().getId());
            } else {
                File f = c.getFile();
                FileCache::insert(f);
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
        ofstream file(GOOGLEDRIVE_CONFIG);
        file << configurationstring;
        file.close();

        /*chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> d1 = t2 - t1;
        chrono::duration<double, milli> d2 = t3 - t2;
        cout << "Request: " << d1.count() << " ms | Fetch: " << d2.count() << " ms | Done: " << (atol(cl.getNextPageToken().c_str()) / end) << "%" << endl;*/
    }
    GoogleDrive::pageToken = cl.getNewStartPageToken();
}

void GoogleDrive::createDirectory(string path) {
    int pos = path.find_last_not_of("/");
    File parent = getFile(path.substr(0, pos));

    File file;
    file.setMimeType("application/vnd.google-apps.folder");
    file.setName(path.substr(pos, path.length()));

    FilesApi::create("", false, false, "", false, false, file);
}

int GoogleDrive::readFile(File file, char *buf, size_t size, off_t offset) {
    return ChunkCache::read(file, buf, size, offset);
}
