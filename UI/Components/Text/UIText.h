#pragma once

#include "Components/UIComponent.h"
#include "Structure/TextMesh.h"

class Font;

enum UITextMode {
    LEFT = 0,
    RIGHT,
    CENTERED,
};

class UIText : public UIComponent {
public:
    UIText(const char* text, int fontSize, float positionX, float positionY, float width, float height, int mode);
    UIText(const char* text, Font* font, int fontSize, float positionX, float positionY, float width, float height, int mode);
    void setPosition(float positionX, float positionY);
    void setSize(float width, float height);
    void setFontSize(int fontSize);
    void setMaxLines(int maxLines);
    void setMode(int mode);
    const char* text;
    int fontSize, maxLines, mode;
    Font* font;
    TextMesh textMesh;
};
