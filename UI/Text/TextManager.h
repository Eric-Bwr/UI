#pragma once

#include <Buffer.h>
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#define DEFAULT_FONT_PATH "C:/Windows/Fonts/Arial.ttf"

class Font;
class FontType;
class UIText;

class TextManager {
public:
    static int init();
    static void loadText(Font* font, UIText* uiText);
    static FT_Library library;
    static Font* defaultFont;
    static VertexBufferObjectLayout bufferObjectLayout;
    ~TextManager();
};
