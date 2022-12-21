#pragma once

#include <OpenGL/Buffer.h>
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "UIDefines.h"

class Font;
class UIText;
class FontType;

class DataManager {
public:
    static int init();
    static FontType* getFontType(UIText *uiText);
    static FontType* getFontType(Font *font, int fontSize);
    static FT_Library library;
    static Font* defaultFont;
    static VertexBufferObjectLayout textLayout;
    static VertexBufferObjectLayout quadLayout;
    ~DataManager();
};