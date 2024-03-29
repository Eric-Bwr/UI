#pragma once

#include <map>
#include <OpenGL/Texture.h>
#include "UI/UIComponents/Text/Font.h"

const int FONT_CHAR_START = 32;
const int FONT_CHAR_END = 126;

struct Character {
    float ascii;
    float width, height;
    float bearingX, bearingY;
    float textureX, textureY;
    float advance;
};

class FontType {
public:
    FontType(Font* font, int fontSize);
    Texture texture;
    float getTextWidth(const char* text);
    float getCharacterWidth(int ascii);
    float getHeight();
    float getOffset();
    ~FontType();
    std::map<int, Character> characters;
    int fontSize;
    float bearing = 0, height = 0;
private:
    float pixelMapped;
    void loadGlyph(int glyph);
    Font* font;
};