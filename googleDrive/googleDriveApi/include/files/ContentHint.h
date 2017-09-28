//
// Created by Matthias Hofstätter on 17.09.17.
//

#ifndef PLEXDRIVE_CONTENTHINT_H
#define PLEXDRIVE_CONTENTHINT_H

#include <string>
#include <document.h>
#include "Thumbnail.h"

using namespace std;

class ContentHint {
private:
    class Thumbnail thumbnail;
    string indexableText;
public:
    ContentHint();
    ContentHint(rapidjson::Document &document);

    Thumbnail &getThumbnail();
    void setThumbnail(Thumbnail &thumbnail);

    string &getIndexableText();
    void setIndexableText(string &indexableText);
};


#endif //PLEXDRIVE_CONTENTHINT_H
