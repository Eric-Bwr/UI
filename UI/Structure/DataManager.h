#pragma once

#include <Buffer.h>
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H"FreeType/include/freetype/freetype.h"

#define DEFAULT_FONT_PATH "C:/Windows/Fonts/Arial.ttf"
#define SHADER_COLOR_NAME "color"

class Font;
class UIText;

class DataManager {
public:
    static int init();
    static void loadText(UIText* uiText);
    static FT_Library library;
    static Font* defaultFont;
    static VertexBufferObjectLayout textLayout;
    static VertexBufferObjectLayout quadLayout;
    ~DataManager();
};