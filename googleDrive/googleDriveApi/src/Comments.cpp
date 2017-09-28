//
// Created by Matthias Hofstätter on 15.09.17.
//

#include "comments/Comments.h"

Comment
Comments::create(string fileId, Comment requestBody, bool alt, string fields, bool prettyPrint,
                               string quotaUser, string userId) {
    return Comment();
}

void Comments::del(string commentId, string fileId, bool alt, string fields, bool prettyPrint,
                                 string quotaUser, string userId) {

}

Comment
Comments::get(string commentId, string fileId, bool includeDeleted, bool alt, string fields,
                            bool prettyPrint, string quotaUser, string userId) {
    return Comment();
}

CommentList Comments::list(string fileId, bool includeDeleted, int pageSize, string pageToken,
                                                  string startModifiedTime, bool alt, string fields, bool prettyPrint,
                                                  string quotaUser, string userId) {
    return CommentList();
}

Comment
Comments::update(string fileId, string commentId, Comment requestBody, bool alt, string fields,
                               bool prettyPrint, string quotaUser, string userId) {
    return Comment();
}
