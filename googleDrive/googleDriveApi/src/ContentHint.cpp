//
// Created by Matthias Hofstätter on 17.09.17.
//

#include "files/ContentHint.h"
#include <files/Thumbnail.h>

ContentHint::ContentHint() {

}

ContentHint::ContentHint(rapidjson::Document &document) {
    if(document.HasMember("Thumbnail")) {
        rapidjson::Document d(rapidjson::kObjectType);
        d.CopyFrom(document["Thumbnail"], d.GetAllocator());
        this->thumbnail = Thumbnail(d);
    }
    if(document.HasMember("indexableText"))
        this->indexableText = document["indexableText"].GetString();
}

Thumbnail &ContentHint::getThumbnail() {
    return thumbnail;
}

void ContentHint::setThumbnail(Thumbnail &thumbnail) {
    ContentHint::thumbnail = thumbnail;
}

string &ContentHint::getIndexableText() {
    return indexableText;
}

void ContentHint::setIndexableText(string &indexableText) {
    ContentHint::indexableText = indexableText;
}
