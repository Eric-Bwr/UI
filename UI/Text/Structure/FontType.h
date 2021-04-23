#pragma once

#include <map>
#include <Texture.h>
#include "../Font.h"

#define FONT_CHAR_START 32
#define FONT_CHAR_END 126

struct Character {
    int ascii;
    int width, height;
    int advanceX;
    //ADD OTHER CHARACTER SPECIFIC DATA
};

class FontType {
public:
    FontType(Font* font, int fontSize);
    Texture* texture;
    std::map<int, Character> characters;
};