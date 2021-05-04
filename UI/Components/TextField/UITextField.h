#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"
#include "../Text/UIText.h"

class UITextField : public UIComponent {
public:
    explicit UITextField(const char* defaultText, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    UITextField(const char* defaultText, float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    void setTexture(Texture* texture);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
	void setBounds(float, float, float, float) override;
    void keyInput(int key, int action, int mods) override;
    void charInput(unsigned int key) override;
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int button, int action) override;
    bool hovered = false, pressed = false;
    float cursorWidth = DEFAULT_CURSOR_WIDTH, cursorPadding = DEFAULT_CURSOR_PADDING;
    const char* defaultText;
    std::string content, cursorContent;
    QuadMesh mesh;
    QuadMesh cursorMesh;
    Texture* texture;
    UIColor bgColor;
    UIColor fgColor;
    UIColor cursorColor;
    UIColor hoveredColor;
    UIColor pressedColor;
    UIText text;
    FontType* fontType;
private:
    void updateCursor();
};
