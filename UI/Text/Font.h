#pragma once

#include "TextManager.h"

class Font {
public:
    explicit Font(const char* path, int faceIndex = 0);
    ~Font();
    FT_GlyphSlot slot;
    int errorCode = 0;
    FT_Face face;
};
