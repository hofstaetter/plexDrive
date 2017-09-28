//
// Created by Matthias Hofstätter on 15.09.17.
//

#ifndef PLEXDRIVE_GOOGLEDRIVEAPICHANNELS_H
#define PLEXDRIVE_GOOGLEDRIVEAPICHANNELS_H

#include <string>
#include "Channel.h"

using namespace std;

class ChannelsApi {
public:
    static void stop(Channel channelsStopRequest,
                     bool alt = false, string fields = "", bool prettyPrint = false, string quotaUser = "", string userId = "");
};


#endif //PLEXDRIVE_GOOGLEDRIVEAPICHANNELS_H
