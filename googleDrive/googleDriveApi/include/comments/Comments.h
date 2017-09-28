//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVEAPICOMMENTS_H
#define PLEXDRIVE_GOOGLEDRIVEAPICOMMENTS_H


#include <string>
#include "Comment.h"
#include "CommentList.h"

class Comments {
    static Comment create(string fileId, Comment requestBody = {},
                                   bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static void del(string commentId, string fileId,
                    bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Comment get(string commentId, string fileId, bool includeDeleted = false,
                                bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static CommentList list(string fileId, bool includeDeleted = false, int pageSize = 20, string pageToken = "", string startModifiedTime = "",
                                     bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Comment update(string fileId, string commentId, Comment requestBody,
                                   bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
};


#endif //PLEXDRIVE_GOOGLEDRIVEAPICOMMENTS_H
