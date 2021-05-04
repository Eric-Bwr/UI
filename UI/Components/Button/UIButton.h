#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../Text/UIText.h"

class UIButton : public UIComponent {
public:
    UIButton(float positionX, float positionY, float width, float height);
    explicit UIButton(float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    void setTexture(Texture* texture);
    void setTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
	void setBounds(float, float, float, float) override;
    void setSize(float width, float height);
    void setText(const char *string, Font* font, int fontSize);
    void setText(const char* text);
    void setFont(Font* font);
    void setFontSize(int fontSize);
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int button, int action) override;
    bool hovered = false, pressed = false;
    QuadMesh mesh;
    QuadMesh hoverMesh;
    QuadMesh pressedMesh;
    Texture* texture;
    UIColor bgColor;
    UIColor fgColor;
	UIColor hoveredColor;
	UIColor pressedColor;
	UIText text;
};