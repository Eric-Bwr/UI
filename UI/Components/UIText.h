#pragma once

#include "Texture.h"

class Font;

class UIText {
public:
    UIText(const char* text, unsigned int fontSize);
    UIText(const char* text, Font* font, unsigned int fontSize);
    const char* text;
    unsigned int fontSize;
    Font* font;
    Texture texture;
};
