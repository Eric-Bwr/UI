#pragma once

#include <OpenGL/Texture.h>
#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"
#include "../../UIColor.h"
#include "../Text/UIText.h"

class UITextArea : public UIComponent {
public:
    void init(float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);
    void init(Font* font, int fontSize, float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);

    void setBackgroundColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor);
    void setBackgroundTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight);
    void setBackgroundTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
    void setBounds(float positionX, float positionY, float width, float height) override;
    void setText(char* text);
    void setFont(Font *font);
    void setFontSize(int fontSize);
    void setLineAdvance(float lineAdvance);
    void setCursorPadding(float cursorPadding);
    void setOffset(float offset);
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
    inline void setButtonCallback(ButtonCallback buttonCallback){ this->buttonCallback = std::move(buttonCallback); }
    inline void setContentCallback(ContentCallback contentCallback){ this->contentCallback = std::move(contentCallback); }

    inline std::string getContent() const { return text.text; }

    void keyInput(int key, int action, int mods) override;
    void charInput(unsigned int key) override;
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int action) override;

    void updateMesh() override;

    bool hovered = false, pressed = false;
    float cursorWidth = CURSOR_WIDTH, cursorPadding = CURSOR_PADDING, offset = 0;
    std::string cursorContent, currentLineContent, currentContentUntilLine;
    QuadMeshTriplet mesh;
    QuadMesh cursorMesh;
    Texture* texture;
    UIColorTriplet bgColor;
    UIColor fgColor;
    UIColor cursorColor;
    UIText text;

    int mode = 0, currentLine = 0, maxLines = 0;
    float fieldWidth = 0, fieldHeight = 0;
    double mouseAdvanceX = 0, mouseAdvanceY = 0;
    void updateUntilLine();
    void updateLine();
    void updateCursor();
    ButtonCallback buttonCallback;
    ContentCallback contentCallback;
};