//
// Created by Matthias Hofstätter on 17.09.17.
//

#include <Capabilities.h>

Capabilities::Capabilities() {
}

Capabilities::Capabilities(rapidjson::Document &document) {
    if(document.HasMember("canAddChildren"))
        this->canAddChildren = document["canAddChildren"].GetBool();
    if(document.HasMember("canChangeTeamDriveBackground"))
        this->canChangeTeamDriveBackground = document["canChangeTeamDriveBackground"].GetBool();
    if(document.HasMember("canComment"))
        this->canComment = document["canComment"].GetBool();
    if(document.HasMember("canCopy"))
        this->canCopy = document["canCopy"].GetBool();
    if(document.HasMember("canDeleteTeamDrive"))
        this->canDeleteTeamDrive = document["canDeleteTeamDrive"].GetBool();
    if(document.HasMember("canDownloader"))
        this->canDownloader = document["canDownloader"].GetBool();
    if(document.HasMember("canEdit"))
        this->canEdit = document["canEdit"].GetBool();
    if(document.HasMember("canListChildren"))
        this->canListChildren = document["canListChildren"].GetBool();
    if(document.HasMember("canManageMembers"))
        this->canManageMembers = document["canManageMembers"].GetBool();
    if(document.HasMember("canReadRevisions"))
        this->canReadRevisions = document["canReadRevisions"].GetBool();
    if(document.HasMember("canRemoveChildren"))
        this->canRemoveChildren = document["canRemoveChildren"].GetBool();
    if(document.HasMember("canRename"))
        this->canRename = document["canRename"].GetBool();
    if(document.HasMember("canRenameTeamDrive"))
        this->canRenameTeamDrive = document["canRenameTeamDrive"].GetBool();
    if(document.HasMember("canShare"))
        this->canShare = document["canShare"].GetBool();
}

bool Capabilities::isCanAddChildren() {
    return canAddChildren;
}

void Capabilities::setCanAddChildren(bool canAddChildren) {
    Capabilities::canAddChildren = canAddChildren;
}

bool Capabilities::isCanChangeTeamDriveBackground() {
    return canChangeTeamDriveBackground;
}

void Capabilities::setCanChangeTeamDriveBackground(bool canChangeTeamDriveBackground) {
    Capabilities::canChangeTeamDriveBackground = canChangeTeamDriveBackground;
}

bool Capabilities::isCanComment() {
    return canComment;
}

void Capabilities::setCanComment(bool canComment) {
    Capabilities::canComment = canComment;
}

bool Capabilities::isCanCopy() {
    return canCopy;
}

void Capabilities::setCanCopy(bool canCopy) {
    Capabilities::canCopy = canCopy;
}

bool Capabilities::isCanDeleteTeamDrive() {
    return canDeleteTeamDrive;
}

void Capabilities::setCanDeleteTeamDrive(bool canDeleteTeamDrive) {
    Capabilities::canDeleteTeamDrive = canDeleteTeamDrive;
}

bool Capabilities::isCanDownloader() {
    return canDownloader;
}

void Capabilities::setCanDownloader(bool canDownloader) {
    Capabilities::canDownloader = canDownloader;
}

bool Capabilities::isCanEdit() {
    return canEdit;
}

void Capabilities::setCanEdit(bool canEdit) {
    Capabilities::canEdit = canEdit;
}

bool Capabilities::isCanListChildren() {
    return canListChildren;
}

void Capabilities::setCanListChildren(bool canListChildren) {
    Capabilities::canListChildren = canListChildren;
}

bool Capabilities::isCanManageMembers() {
    return canManageMembers;
}

void Capabilities::setCanManageMembers(bool canManageMembers) {
    Capabilities::canManageMembers = canManageMembers;
}

bool Capabilities::isCanReadRevisions() {
    return canReadRevisions;
}

void Capabilities::setCanReadRevisions(bool canReadRevisions) {
    Capabilities::canReadRevisions = canReadRevisions;
}

bool Capabilities::isCanRemoveChildren() {
    return canRemoveChildren;
}

void Capabilities::setCanRemoveChildren(bool canRemoveChildren) {
    Capabilities::canRemoveChildren = canRemoveChildren;
}

bool Capabilities::isCanRename() {
    return canRename;
}

void Capabilities::setCanRename(bool canRename) {
    Capabilities::canRename = canRename;
}

bool Capabilities::isCanRenameTeamDrive() {
    return canRenameTeamDrive;
}

void Capabilities::setCanRenameTeamDrive(bool canRenameTeamDrive) {
    Capabilities::canRenameTeamDrive = canRenameTeamDrive;
}

bool Capabilities::isCanShare() {
    return canShare;
}

void Capabilities::setCanShare(bool canShare) {
    Capabilities::canShare = canShare;
}
