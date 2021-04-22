#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#define DEFAULT_FONT_PATH "C:/Windows/Fonts/Arial.ttf"

class Font;
class UIText;

class TextManager {
public:
    static int init();
    static void loadText(const char* text, Font* font, unsigned int fontSize, UIText* uiText);
    static FT_Library library;
    static Font* defaultFont;
    ~TextManager();
};
