//
// Created by Matthias Hofstätter on 19.09.17.
//

#include <changes/Change.h>
#include <changes/ChangesApi.h>
#include <files/File.h>
#include <fstream>
#include <thread>
#include "googleDrive.h"

File googleDrive::root;
string googleDrive::pageToken;

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

File googleDrive::getFile(string path) {
    File current = googleDrive::root;
    vector<string> folders = splitPath(path, '/');
    folders = vector<string>(folders.begin() + 1, folders.end());

    for(string i : folders) {
        for(string j : current.getParents()) {
            if((current = getFromCache(j)).getName() == i) {
                break;
            }
        }
    }

    vector<string> p = getParents(current.getId());
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

vector<File> googleDrive::getDirectory(string path) {
    vector<File> result;

    for(string s : googleDrive::getChildren(getFile(path).getId())) {
        result.push_back(getFromCache(s));
    }

    return result;
}

void googleDrive::init() {
    googleDrive::initCache();

    googleDrive::root = Files::get("root", false, false, "", "id,name,mimeType,modifiedTime,size");
    insertIntoCache(googleDrive::root);

    googleDrive::workOffChanges();
}

void googleDrive::insertIntoCache(File f) {
    //open db
    sqlite3 *db;
    int sr = sqlite3_open("cache.sqlite", &db);

    if(sr != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    //insert File
    sqlite3_stmt *insertStatement;

    sr = sqlite3_prepare_v2(db, "INSERT OR REPLACE INTO file(id, name, mimeType, webContentLink, modifiedTime, size) VALUES(?1, ?2, ?3, ?4, ?5, ?6);", -1, &insertStatement, NULL);
    sr = sqlite3_bind_text(insertStatement, 1, f.getId().c_str(), -1, SQLITE_STATIC);
    sr = sqlite3_bind_text(insertStatement, 2, f.getName().c_str(), -1, SQLITE_STATIC);
    sr = sqlite3_bind_text(insertStatement, 3, f.getMimeType().c_str(), -1, SQLITE_STATIC);
    sr = sqlite3_bind_text(insertStatement, 4, f.getWebContentLink().c_str(), -1, SQLITE_STATIC);
    sr = sqlite3_bind_text(insertStatement, 5, f.getModifiedTime().c_str(), -1, SQLITE_STATIC);
    ostringstream ss;
    ss << f.getSize();
    sr = sqlite3_bind_text(insertStatement, 6, ss.str().c_str(), -1, SQLITE_STATIC);
    sr = sqlite3_step(insertStatement);

    if(sr != SQLITE_DONE) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sr = sqlite3_reset(insertStatement);

    //insert parents
    for(string s : f.getParents()) {
        sr = sqlite3_prepare_v2(db, "INSERT OR REPLACE INTO parent(child, parent) VALUES(?1, ?2);", -1, &insertStatement, NULL);
        sr = sqlite3_bind_text(insertStatement, 1, f.getId().c_str(), -1, SQLITE_STATIC);
        sr = sqlite3_bind_text(insertStatement, 2, s.c_str(), -1, SQLITE_STATIC);
        sr = sqlite3_step(insertStatement);
        if(sr != SQLITE_DONE) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
        }
    }
    //sr = sqlite3_column_int(insertStatement, 0);
    sr = sqlite3_reset(insertStatement);
    sqlite3_finalize(insertStatement);

    sqlite3_close(db);
}

void googleDrive::deleteFromCache(string fileId) {
    //cout << "Deleting: " << f.getId() << endl;
    sqlite3 *db;
    int rc = sqlite3_open("cache.sqlite", &db);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sqlite3_stmt *stmt;

    int res = sqlite3_prepare_v2(db, "DELETE FROM file WHERE id = '?1';", -1, &stmt, NULL);
    res = sqlite3_bind_text(stmt, 1, fileId.c_str(), -1, SQLITE_STATIC);
    res = sqlite3_step(stmt);
    if(res != SQLITE_DONE) {
        throw -1;
    }
    res = sqlite3_prepare_v2(db, "DELETE FROM parent WHERE child = '?1';", -1, &stmt, NULL);
    res = sqlite3_bind_text(stmt, 1, fileId.c_str(), -1, SQLITE_STATIC);
    res = sqlite3_step(stmt);
    if(res != SQLITE_DONE) {
        throw -1;
    }
    int result = sqlite3_column_int(stmt, 0);
    res = sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    sqlite3_close(db);
}

vector<string> googleDrive::getParents(string fileId) {
    sqlite3 *db;
    int sr = sqlite3_open("cache.sqlite", &db);

    if(sr != SQLITE_OK) {
        fprintf(stderr, "OPEN: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    sqlite3_stmt *stmt;
    vector<string> result;

    sr = sqlite3_prepare_v2(db, "SELECT * FROM parent WHERE child = ?1;", -1, &stmt, NULL);
    if(sr != SQLITE_OK) {
        fprintf(stderr, "PREP: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    sr = sqlite3_bind_text(stmt, 1, fileId.c_str(), -1, SQLITE_STATIC);
    if(sr != SQLITE_OK) {
        fprintf(stderr, "BIND: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    sr = sqlite3_step(stmt);
    if(sr != SQLITE_DONE) {
        fprintf(stderr, "STEP: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    while((sr = sqlite3_step(stmt)) == SQLITE_ROW) {
        result.emplace_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return vector<string>();
}

File googleDrive::getFromCache(string fileId) {
    sqlite3 *db;
    int sr = sqlite3_open("cache.sqlite", &db);

    if(sr != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sqlite3_stmt *stmt;
    File result;

    sr = sqlite3_prepare_v2(db, "SELECT FROM File WHERE id = '?1';", -1, &stmt, NULL);
    sr = sqlite3_bind_text(stmt, 1, fileId.c_str(), -1, SQLITE_STATIC);
    while((sr = sqlite3_step(stmt)) == SQLITE_ROW) {
        string s(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        result.setId(s);
        s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        result.setName(s);
        s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        result.setMimeType(s);
        s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        result.setWebContentLink(s);
        s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        result.setModifiedTime(s);
        result.setSize(sqlite3_column_int(stmt, 5));
        sqlite3_stmt *stmt2;
        sr = sqlite3_prepare_v2(db, "SELECT FROM parents WHERE child = '?1';", -1, &stmt2, NULL);
        sr = sqlite3_bind_text(stmt2, 1, fileId.c_str(), -1, SQLITE_STATIC);
        while((sr = sqlite3_step(stmt2)) == SQLITE_ROW) {
            result.getParents().emplace_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1))));
        }
        if(sr != SQLITE_DONE) {
            throw -1;
        }
    }
    if(sr != SQLITE_DONE) {
        throw -1;
    }


    sqlite3_finalize(stmt);
    return File();

    sqlite3_close(db);
}

void googleDrive::workOffChanges() {
    if(googleDrive::pageToken.empty()) {
        googleDrive::pageToken = "1";
        rapidjson::Document configuration(rapidjson::kObjectType);
        ifstream file("googleDrive.json");
        if (file.is_open()) {
            string configurationstring;
            file >> configurationstring;
            file.close();

            configuration.Parse(configurationstring.c_str());
            if (configuration.IsObject()) {
                if (configuration.HasMember("nextPageToken"))
                    googleDrive::pageToken = configuration["nextPageToken"].GetString();
            }
        }
    }

    //%
    long end = atol(ChangesApi::getStartPageToken().getStartPageToken().c_str());

    ChangeList cl;
    cl.setNextPageToken(googleDrive::pageToken);
    while(!cl.getNextPageToken().empty()) {
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        cl = ChangesApi::list(cl.getNextPageToken(), false, true, false, 1000, false, "", false, "", false, "nextPageToken,newStartPageToken,changes/removed,changes/file/id,changes/file/name,changes/file/mimeType,changes/file/webContentLink,changes/file/modifiedTime,changes/file/size,changes/file/parents");

        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        for(Change c : cl.getChanges()) {
            if(c.isRemoved()) {
                deleteFromCache(c.getFile().getId());
            } else {
                insertIntoCache(c.getFile());
            }
        }

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

        chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> d1 = t2 - t1;
        chrono::duration<double, milli> d2 = t3 - t2;
        cout << "Request: " << d1.count() << " ms | Fetch: " << d2.count() << " ms | Done: " << (atol(cl.getNextPageToken().c_str()) / (end / 100)) << "%" << endl;
    }
    googleDrive::pageToken = cl.getNewStartPageToken();
}

void googleDrive::initCache() {
/* INIT DB */
    sqlite3 *db;
    int rc = sqlite3_open("cache.sqlite", &db);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS file(id TEXT PRIMARY_KEY NOT NULL, name TEXT NOT NULL, mimeType TEXT NOT NULL, webContentLink TEXT, modifiedTime TEXT NOT NULL, size INTEGER NOT NULL);", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    rc = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS parent(child TEXT NOT NULL, parent TEXT NOT NULL, PRIMARY KEY(child, parent), FOREIGN KEY(child) REFERENCES File(id), FOREIGN KEY(parent) REFERENCES File(id));", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    rc = sqlite3_prepare_v2(db, "CREATE INDEX IF NOT EXISTS fileIdIndex ON File(id);", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    rc = sqlite3_prepare_v2(db, "CREATE INDEX IF NOT EXISTS parentChildIndex ON parent(child);", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    rc = sqlite3_prepare_v2(db, "CREATE INDEX IF NOT EXISTS parentParentIndex ON parent(parent);", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sqlite3_finalize(stmt);
    /* INIT DB END */
}

vector<string> googleDrive::getChildren(string fileId) {
    sqlite3 *db;
    int sr = sqlite3_open("cache.sqlite", &db);

    if(sr != SQLITE_OK) {
        fprintf(stderr, "OPEN: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    sqlite3_stmt *stmt;
    vector<string> result;

    sr = sqlite3_prepare_v2(db, "SELECT * FROM parent WHERE parent = ?1;", -1, &stmt, NULL);
    if(sr != SQLITE_OK) {
        fprintf(stderr, "PREP: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    sr = sqlite3_bind_text(stmt, 1, fileId.c_str(), -1, SQLITE_STATIC);
    if(sr != SQLITE_OK) {
        fprintf(stderr, "BIND: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    sr = sqlite3_step(stmt);
    if(sr != SQLITE_DONE) {
        fprintf(stderr, "STEP: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw -1;
    }
    while((sr = sqlite3_step(stmt)) == SQLITE_ROW) {
        result.emplace_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
    }


    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return vector<string>();
}
