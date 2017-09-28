//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_REVISIONLIST_H
#define PLEXDRIVE_REVISIONLIST_H


#include <revisions/Revision.h>
#include <string>
#include <vector>

using namespace std;

class RevisionList {
private:
    string kind;
    string nextPageToken;
    vector<Revision> revisions;
public:
    RevisionList();
    RevisionList(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getNextPageToken();
    void setNextPageToken(string &nextPageToken);

    vector<Revision> &getRevisions();
    void setRevisions(vector<Revision> &revisions);
};


#endif //PLEXDRIVE_REVISIONLIST_H
