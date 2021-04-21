#pragma once

#include "TextManager.h"

class Font {
public:
    bool init(const char* path, int faceIndex = 0);
    bool setSize(unsigned int width, unsigned int height);
    ~Font();
private:
    FT_Face face;
};
