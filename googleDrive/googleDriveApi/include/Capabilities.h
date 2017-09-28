//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_CAPABILITIES_H
#define PLEXDRIVE_CAPABILITIES_H

#include <document.h>

using namespace std;

class Capabilities {
private:
    bool canAddChildren;
    bool canChangeTeamDriveBackground;
    bool canComment;
    bool canCopy;
    bool canDeleteTeamDrive;
    bool canDownloader;
    bool canEdit;
    bool canListChildren;
    bool canManageMembers;
    bool canReadRevisions;
    bool canRemoveChildren;
    bool canRename;
    bool canRenameTeamDrive;
    bool canShare;
    
public:
    Capabilities();
    Capabilities(rapidjson::Document &document);

    bool isCanAddChildren();
    void setCanAddChildren(bool canAddChildren);

    bool isCanChangeTeamDriveBackground();
    void setCanChangeTeamDriveBackground(bool canChangeTeamDriveBackground);

    bool isCanComment();
    void setCanComment(bool canComment);

    bool isCanCopy();
    void setCanCopy(bool canCopy);

    bool isCanDeleteTeamDrive();
    void setCanDeleteTeamDrive(bool canDeleteTeamDrive);

    bool isCanDownloader();
    void setCanDownloader(bool canDownloader);

    bool isCanEdit();
    void setCanEdit(bool canEdit);

    bool isCanListChildren();
    void setCanListChildren(bool canListChildren);

    bool isCanManageMembers();
    void setCanManageMembers(bool canManageMembers);

    bool isCanReadRevisions();
    void setCanReadRevisions(bool canReadRevisions);

    bool isCanRemoveChildren();
    void setCanRemoveChildren(bool canRemoveChildren);

    bool isCanRename();
    void setCanRename(bool canRename);

    bool isCanRenameTeamDrive();
    void setCanRenameTeamDrive(bool canRenameTeamDrive);

    bool isCanShare();
    void setCanShare(bool canShare);
};


#endif //PLEXDRIVE_CAPABILITIES_H
