#pragma once

#include "UI/UIStructure/DataManager.h"

class Font {
public:
    void init(const char* path, int faceIndex = 0);
    ~Font();

    const char* path;
    int errorCode = 0;
    FT_Face face;
};
