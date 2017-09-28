//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_REPLIESGOOGLEDRIVEAPI_H
#define PLEXDRIVE_REPLIESGOOGLEDRIVEAPI_H


#include <replies/Reply.h>
#include <replies/ReplyList.h>

class Replies {
public:
    static Reply create(string fileId, string commentId, Reply requestBody,
                                  bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static void del(string fileId, string commentId, string replyId,
                    bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Reply get(string fileId, string commentId, string replyId, bool includeDeleted = false,
                               bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static ReplyList list(string fileId, string commentId, bool includeDeleted = false, int pageSize = 20, string pageToken = "",
                          bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
    static Reply update(string fileId, string commentId, string replyId, Reply requestBody,
                        bool alt = false, std::string fields = "", bool prettyPrint = false, std::string quotaUser = "", std::string userId = "");
};


#endif //PLEXDRIVE_REPLIESGOOGLEDRIVEAPI_H
