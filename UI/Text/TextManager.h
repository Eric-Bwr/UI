#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

class TextManager {
public:
    static int init();
    static FT_Library library;
};
