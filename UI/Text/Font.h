#pragma once

#include "TextManager.h"

class Font {
public:
    bool init(const char* path, int faceIndex = 0);
    ~Font();
private:
    FT_Face face;
};
