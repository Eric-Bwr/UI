#pragma once

#include <Buffer.h>
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#define DEFAULT_FONT_PATH "C:/Windows/Fonts/Arial.ttf"

class Font;
class UIText;

class TextManager {
public:
    static int init();
    static void loadText(UIText* uiText);
    static void setSize(int width, int height);
    static FT_Library library;
    static Font* defaultFont;
    static VertexBufferObjectLayout bufferObjectLayout;
    static int windowWidth, windowHeight;
    ~TextManager();
};
