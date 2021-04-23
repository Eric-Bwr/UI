#pragma once

#include <map>
#include <Texture.h>
#include "../Font.h"

const int FONT_CHAR_START = 32;
const int FONT_CHAR_END = 126;

struct Character {
    int ascii;
    int width, height;
    int bearingX, bearingY;
    int advance;
};

class FontType {
public:
    FontType(Font* font, int fontSize);
    Texture* texture;
    std::map<int, Character> characters;
    int fontSize;
};