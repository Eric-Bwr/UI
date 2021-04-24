#pragma once

#include <Buffer.h>
#include "../Text/Structure/TextMesh.h"

class Font;

class UIText {
public:
    UIText(const char* text, int fontSize, float positionX, float positionY);
    UIText(const char* text, Font* font, int fontSize, float positionX, float positionY);
    const char* text;
    int fontSize;
    Font* font;
    float positionX, positionY;
    TextMesh textMesh;
};
