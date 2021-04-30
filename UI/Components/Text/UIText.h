#pragma once

#include "Components/UIComponent.h"
#include "Structure/TextMesh.h"
#include "../../UIColor.h"

class Font;

enum UITextMode {
    LEFT = 0,
    RIGHT,
    CENTERED,
    CENTERED_HORIZONTAL,
    CENTERED_VERTICAL_RIGHT,
    CENTERED_VERTICAL_LEFT
};

class UIText : public UIComponent, public UIColor {
public:
    UIText(const char* text, int fontSize, float positionX, float positionY, float width, float height, int mode);
    UIText(const char* text, Font* font, int fontSize, float positionX, float positionY, float width, float height, int mode);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
    void setFontSize(int fontSize);
    void setMode(int mode);
    const char* text;
    int fontSize, mode;
    Font* font;
    TextMesh textMesh;
};
