#pragma once

#include "Structure/DataManager.h"

class Font {
public:
    explicit Font(const char* path, int faceIndex = 0);
    ~Font();
    const char* path;
    FT_GlyphSlot slot;
    int errorCode = 0;
    FT_Face face;
};
