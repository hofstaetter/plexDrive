//
// Created by Matthias Hofstätter on 18.09.17.
//

#ifndef PLEXDRIVE_STORAGEQUOTA_H
#define PLEXDRIVE_STORAGEQUOTA_H

#include <document.h>

class StorageQuota {
private:
    long limit;
    long usage;
    long usageInDrive;
    long usageInDriveTrash;
public:
    StorageQuota();
    StorageQuota(rapidjson::Document &document);

    long getLimit() const;

    void setLimit(long limit);

    long getUsage() const;

    void setUsage(long usage);

    long getUsageInDrive() const;

    void setUsageInDrive(long usageInDrive);

    long getUsageInDriveTrash() const;

    void setUsageInDriveTrash(long usageInDriveTrash);
};


#endif //PLEXDRIVE_STORAGEQUOTA_H
