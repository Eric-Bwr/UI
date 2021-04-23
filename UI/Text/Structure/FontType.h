#pragma once

#include <map>
#include <Texture.h>
#include "../Font.h"

#define FONT_CHAR_START 65
#define FONT_CHAR_END 72

struct Character {
    int ascii;
    //ADD OTHER CHARACTER SPECIFIC DATA
};

class FontType {
public:
    FontType(Font* font, int fontSize);
    Texture* texture;
    std::map<int, Character> characters;
};