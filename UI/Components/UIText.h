#pragma once

#include "Texture.h"

class Font;

class UIText {
public:
    UIText(const char* text, int fontSize);
    UIText(const char* text, Font* font, int fontSize);
    const char* text;
    int fontSize;
    Font* font;
};
