#pragma once

#include <Buffer.h>
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#define DEFAULT_FONT_PATH "C:/Windows/Fonts/Arial.ttf"
#define SHADER_COLOR_NAME "color"
#define DEFAULT_WIDTH 140
#define DEFAULT_HEIGHT 30

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