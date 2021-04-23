#pragma once

#include <Buffer.h>
#include "../Text/Structure/TextMesh.h"

class Font;

class UIText {
public:
    UIText(const char* text, int fontSize);
    UIText(const char* text, Font* font, int fontSize);
    const char* text;
    int fontSize;
    Font* font;
    TextMesh textMesh;
};
