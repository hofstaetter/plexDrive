//
// Created by Matthias Hofstätter on 18.09.17.
//

#include "about/StorageQuota.h"

StorageQuota::StorageQuota() {

}

StorageQuota::StorageQuota(rapidjson::Document &document) {
    throw -2;
}

long StorageQuota::getLimit() const {
    return limit;
}

void StorageQuota::setLimit(long limit) {
    StorageQuota::limit = limit;
}

long StorageQuota::getUsage() const {
    return usage;
}

void StorageQuota::setUsage(long usage) {
    StorageQuota::usage = usage;
}

long StorageQuota::getUsageInDrive() const {
    return usageInDrive;
}

void StorageQuota::setUsageInDrive(long usageInDrive) {
    StorageQuota::usageInDrive = usageInDrive;
}

long StorageQuota::getUsageInDriveTrash() const {
    return usageInDriveTrash;
}

void StorageQuota::setUsageInDriveTrash(long usageInDriveTrash) {
    StorageQuota::usageInDriveTrash = usageInDriveTrash;
}
