#pragma once

#include <Buffer.h>
#include "../Text/Structure/TextMesh.h"

class Font;

class UIText {
public:
    UIText(const char* text, int fontSize, float positionX, float positionY, float width, float height);
    UIText(const char* text, Font* font, int fontSize, float positionX, float positionY, float width, float height);
    void setMaxLines(int maxLines);
    const char* text;
    int fontSize, maxLines;
    Font* font;
    float positionX, positionY, width, height;
    TextMesh textMesh;
};
