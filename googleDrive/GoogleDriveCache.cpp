//
// Created by Matthias Hofstätter on 29.09.17.
//

#include "GoogleDriveCache.h"

string GoogleDriveCache::Path = "";

void GoogleDriveCache::init(string path) {
    GoogleDriveCache::Path = path;

    GoogleDriveCache::prepareDb();
}

void GoogleDriveCache::prepareDb() {
    sqlite3 *database;
    int resultCode = sqlite3_open(GoogleDriveCache::Path.c_str(), &database);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::initCache sqlite3_open()";
        sqlite3_close(database);
        throw -1;
    }

    sqlite3_stmt *stmt;
    resultCode = sqlite3_prepare_v2(database, "CREATE TABLE IF NOT EXISTS file(id TEXT PRIMARY_KEY NOT NULL, name TEXT NOT NULL, mimeType TEXT NOT NULL, webContentLink TEXT, viewedByMeTime INTEGER NOT NULL, modifiedTime INTEGET NOT NULL, size INTEGER NOT NULL);", -1, &stmt, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::initCache sqlite3_prepare_v2(" << "CREATE TABLE IF NOT EXISTS file(id TEXT PRIMARY_KEY NOT NULL, name TEXT NOT NULL, mimeType TEXT NOT NULL, webContentLink TEXT, modifiedTime TEXT NOT NULL, size INTEGER NOT NULL);" << ")";
        sqlite3_close(database);
        throw -1;
    }
    resultCode = sqlite3_step(stmt);
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::initCache sqlite3_step failed";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_prepare_v2(database, "CREATE TABLE IF NOT EXISTS parent(child TEXT NOT NULL, parent TEXT NOT NULL, PRIMARY KEY(child, parent), FOREIGN KEY(child) REFERENCES File(id), FOREIGN KEY(parent) REFERENCES File(id));", -1, &stmt, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::initCache sqlite3_prepare_v2(" << "CREATE TABLE IF NOT EXISTS parent(child TEXT NOT NULL, parent TEXT NOT NULL, PRIMARY KEY(child, parent), FOREIGN KEY(child) REFERENCES File(id), FOREIGN KEY(parent) REFERENCES File(id));" << ")";
        sqlite3_close(database);
        throw -1;
    }
    resultCode = sqlite3_step(stmt);
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::initCache sqlite3_step failed";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_prepare_v2(database, "CREATE INDEX IF NOT EXISTS fileIdIndex ON File(id);", -1, &stmt, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::initCache sqlite3_prepare_v2(" << "CREATE INDEX IF NOT EXISTS fileIdIndex ON File(id);" << ")";
        sqlite3_close(database);
        throw -1;
    }
    resultCode = sqlite3_step(stmt);
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::initCache sqlite3_step failed";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_prepare_v2(database, "CREATE INDEX IF NOT EXISTS parentChildIndex ON parent(child);", -1, &stmt, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::initCache sqlite3_prepare_v2(" << "CREATE INDEX IF NOT EXISTS parentChildIndex ON parent(child);" << ")";
        sqlite3_close(database);
        throw -1;
    }
    resultCode = sqlite3_step(stmt);
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::initCache sqlite3_step failed";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_prepare_v2(database, "CREATE INDEX IF NOT EXISTS parentParentIndex ON parent(parent);", -1, &stmt, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::initCache sqlite3_prepare_v2(" << "CREATE INDEX IF NOT EXISTS parentParentIndex ON parent(parent);" << ")";
        sqlite3_close(database);
        throw -1;
    }
    resultCode = sqlite3_step(stmt);
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::initCache sqlite3_step failed";
        sqlite3_close(database);
        throw -1;
    }

    sqlite3_finalize(stmt);
}

void GoogleDriveCache::insert(File f) {
    sqlite3 *database;
    int resultCode = sqlite3_open(GoogleDriveCache::Path.c_str(), &database);
    if(resultCode != SQLITE_OK) {
        cout << "Can't open database";
        sqlite3_close(database);
        throw -1;
    }
    
    sqlite3_stmt *insertStatement;

    resultCode = sqlite3_prepare_v2(database, "INSERT OR REPLACE INTO file(id, name, mimeType, webContentLink, viewedByMeTime, modifiedTime, size) VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7);", -1, &insertStatement, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_prepare_v2(" << "INSERT OR REPLACE INTO file(id, name, mimeType, webContentLink, modifiedTime, size) VALUES(?1, ?2, ?3, ?4, ?5, ?6);" << ")";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(insertStatement, 1, f.getId().c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 1 << ", " << f.getId() << ")";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(insertStatement, 2, f.getName().c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 2 << ", " << f.getName() << ")";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(insertStatement, 3, f.getMimeType().c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 3 << ", " << f.getMimeType() << ")";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(insertStatement, 4, f.getWebContentLink().c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 4 << ", " << f.getWebContentLink() << ")";
        sqlite3_close(database);
        throw -1;
    }

    long long int temp = static_cast<long long int>(f.getViewedByMeTime());
    resultCode = sqlite3_bind_int64(insertStatement, 5, temp);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 5 << ", " << f.getModifiedTime() << ")";
        sqlite3_close(database);
        throw -1;
    }

    temp = static_cast<long long int>(f.getModifiedTime());
    resultCode = sqlite3_bind_int64(insertStatement, 6, temp);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 5 << ", " << f.getModifiedTime() << ")";
        sqlite3_close(database);
        throw -1;
    }
    ostringstream ss;
    ss << f.getSize();
    resultCode = sqlite3_bind_text(insertStatement, 7, ss.str().c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 6 << ", " << ss.str() << ")";
        sqlite3_close(database);
        throw -1;
    }
    resultCode = sqlite3_step(insertStatement);
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::insertIntoCache sqlite3_step()";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_reset(insertStatement);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_reset()";
        sqlite3_close(database);
        throw -1;
    }

    //insert parents
    for(string s : f.getParents()) {
        resultCode = sqlite3_prepare_v2(database, "INSERT OR REPLACE INTO parent(child, parent) VALUES(?1, ?2);", -1, &insertStatement, NULL);
        if(resultCode != SQLITE_OK) {
            cout << "GoogleDrive::insertIntoCache sqlite3_prepare_v2(" << "INSERT OR REPLACE INTO parent(child, parent) VALUES(?1, ?2);" << ")";
            sqlite3_close(database);
            throw -1;
        }

        resultCode = sqlite3_bind_text(insertStatement, 1, f.getId().c_str(), -1, SQLITE_STATIC);
        if(resultCode != SQLITE_OK) {
            cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 1 << ", " << f.getId() << ")";
            sqlite3_close(database);
            throw -1;
        }

        resultCode = sqlite3_bind_text(insertStatement, 2, s.c_str(), -1, SQLITE_STATIC);
        if(resultCode != SQLITE_OK) {
            cout << "GoogleDrive::insertIntoCache sqlite3_bind_text(" << 2 << ", " << s << ")";
            sqlite3_close(database);
            throw -1;
        }

        resultCode = sqlite3_step(insertStatement);
        if(resultCode != SQLITE_DONE) {
            cout << "GoogleDrive::insertIntoCache sqlite3_step()";
            sqlite3_close(database);
            throw -1;
        }

        resultCode = sqlite3_reset(insertStatement);
        if(resultCode != SQLITE_OK) {
            cout << "GoogleDrive::insertIntoCache sqlite3_reset()";
            sqlite3_close(database);
            throw -1;
        }
    }

    sqlite3_finalize(insertStatement);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::insertIntoCache sqlite3_reset()";
        sqlite3_close(database);
        throw -1;
    }
}

void GoogleDriveCache::remove(string fileId) {
    sqlite3 *database;
    int resultCode = sqlite3_open(GoogleDriveCache::Path.c_str(), &database);
    if(resultCode != SQLITE_OK) {
        cout << "Can't open database";
        sqlite3_close(database);
        throw -1;
    }

    sqlite3_stmt *deleteStatement;

    resultCode = sqlite3_prepare_v2(database, "DELETE FROM file WHERE id = '?1';", -1, &deleteStatement, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(deleteStatement, 1, fileId.c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }
    
    resultCode = sqlite3_step(deleteStatement);
    if(resultCode != SQLITE_DONE) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }
    
    resultCode = sqlite3_reset(deleteStatement);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }
    
    resultCode = sqlite3_prepare_v2(database, "DELETE FROM parent WHERE child = '?1';", -1, &deleteStatement, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(deleteStatement, 1, fileId.c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_step(deleteStatement);
    if(resultCode != SQLITE_DONE) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    sqlite3_finalize(deleteStatement);
}

File &GoogleDriveCache::get(string fileId) {
    sqlite3 *database;
    int resultCode = sqlite3_open(GoogleDriveCache::Path.c_str(), &database);
    if(resultCode != SQLITE_OK) {
        cout << "Can't open database";
        sqlite3_close(database);
        throw -1;
    }

    sqlite3_stmt *selectFileStatement, *selectParentsStatement;;

    resultCode = sqlite3_prepare_v2(database, "SELECT FROM File WHERE id = '?1';", -1, &selectFileStatement, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(selectFileStatement, 1, fileId.c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    File result;

    while((resultCode = sqlite3_step(selectFileStatement)) == SQLITE_ROW) {
        string s(reinterpret_cast<const char*>(sqlite3_column_text(selectFileStatement, 0)));
        result.setId(s);

        s = reinterpret_cast<const char*>(sqlite3_column_text(selectFileStatement, 1));
        result.setName(s);

        s = reinterpret_cast<const char*>(sqlite3_column_text(selectFileStatement, 2));
        result.setMimeType(s);

        s = reinterpret_cast<const char*>(sqlite3_column_text(selectFileStatement, 3));
        result.setWebContentLink(s);

        long temp = (long)sqlite3_column_int64(selectFileStatement, 4);
        result.setViewedByMeTime(temp);

        temp = (long)sqlite3_column_int64(selectFileStatement, 5);
        result.setModifiedTime(temp);

        result.setSize(sqlite3_column_int(selectFileStatement, 6));

        resultCode = sqlite3_prepare_v2(database, "SELECT FROM parents WHERE child = '?1';", -1, &selectParentsStatement, NULL);
        if(resultCode != SQLITE_OK) {
            cout << "ERROR";
            sqlite3_close(database);
            throw -1;
        }

        resultCode = sqlite3_bind_text(selectParentsStatement, 1, fileId.c_str(), -1, SQLITE_STATIC);
        if(resultCode != SQLITE_OK) {
            cout << "ERROR";
            sqlite3_close(database);
            throw -1;
        }

        while((resultCode = sqlite3_step(selectParentsStatement)) == SQLITE_ROW) {
            result.getParents().emplace_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(selectParentsStatement, 1))));
        }
        if(resultCode != SQLITE_DONE) {
            cout << "ERROR";
            sqlite3_close(database);
            throw -1;
        }

        resultCode = sqlite3_reset(selectParentsStatement);
        if(resultCode != SQLITE_OK) {
            cout << "ERROR";
            sqlite3_close(database);
            throw -1;
        }
    }
    if(resultCode != SQLITE_DONE) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_finalize(selectFileStatement);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_finalize(selectParentsStatement);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    return result;
}

vector<string> GoogleDriveCache::getChildren(string fileId) {
    sqlite3 *database;
    int resultCode = sqlite3_open(GoogleDriveCache::Path.c_str(), &database);
    if(resultCode != SQLITE_OK) {
        cout << "Can't open database";
        sqlite3_close(database);
        throw -1;
    }
    
    sqlite3_stmt *selectParentsStatement;
    vector<string> result;

    resultCode = sqlite3_prepare_v2(database, "SELECT * FROM parent WHERE parent = ?1;", -1, &selectParentsStatement, NULL);
    if(resultCode != SQLITE_OK) {
        cout << "GoogleDrive::getChildren sqlite3_prepare_v2(" << "SELECT * FROM parent WHERE parent = ?1;" << ")";
        sqlite3_close(database);
        throw -1;
    }

    resultCode = sqlite3_bind_text(selectParentsStatement, 1, fileId.c_str(), -1, SQLITE_STATIC);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }

    while((resultCode = sqlite3_step(selectParentsStatement)) == SQLITE_ROW) {
        result.emplace_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(selectParentsStatement, 1))));
    }
    if(resultCode != SQLITE_DONE) {
        cout << "GoogleDrive::getChildren sqlite3_step()";
        sqlite3_close(database);
        throw -1;
    }


    sqlite3_finalize(selectParentsStatement);
    if(resultCode != SQLITE_OK) {
        cout << "ERROR";
        sqlite3_close(database);
        throw -1;
    }
    
    return result;
}
