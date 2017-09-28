//
// Created by Matthias Hofstätter on 14.09.17.
//

#ifndef PLEXDRIVE_CHANGESLISTRESPNSE_H
#define PLEXDRIVE_CHANGESLISTRESPNSE_H

#include <string>
#include <vector>
#include "Change.h"

using namespace std;

class ChangeList {
private:
    string kind;
    string nextPageToken;
    string newStartPageToken;
    vector<Change> changes;
public:
    /*string getKind();

    void setKind(string kind);

    string getNextPageToken();

    void setNextPageToken(string nextPageToken);

    string getNewStartPageToken();

    void setNewStartPageToken(string newStartPageToken);

    vector<Change> getChanges();

    void setChanges(vector<Change> changes);*/

    ChangeList();
    ChangeList(rapidjson::Document &document);

    string &getKind();
    void setKind(string &kind);

    string &getNextPageToken();
    void setNextPageToken(string &nextPageToken);

    string &getNewStartPageToken();
    void setNewStartPageToken(string &newStartPageToken);

    vector<Change> &getChanges();
    void setChanges(vector<Change> &changes);
};


#endif //PLEXDRIVE_CHANGESLISTRESPNSE_H
