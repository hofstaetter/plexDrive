//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_REVISIONS_H
#define PLEXDRIVE_REVISIONS_H


#include <string>
#include <revisions/Revision.h>
#include <revisions/RevisionList.h>

using namespace std;

class Revisions {
public:
    static void del(string fileId, string revisionId,
                    bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Revision get(string fileId, string revisionId, bool acknowledgeAbuse = false,
                        bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static RevisionList list(string fileId, int pageSize = 200, string pageToken = "",
                             bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Revision update(string fileId, string revisionId, Revision requestBody,
                           bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
};


#endif //PLEXDRIVE_REVISIONS_H
