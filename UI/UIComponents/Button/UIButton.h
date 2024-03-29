#pragma once

#include <OpenGL/Texture.h>
#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"
#include "../Text/UIText.h"

class UIButton : public UIComponent {
public:
    void init(float positionX = 0.0f, float positionY = 0.0f, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    void init(char* text, Font* font, int fontSize, int mode, float positionX = 0.0f, float positionY = 0.0f, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    void setBackgroundColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor);
    void setBackgroundTexture(Texture* texture);
    void setBackgroundTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight);
    void setBackgroundTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
	void setBounds(float positionX, float positionY, float width, float height) override;
    void setSize(float width, float height);
    void setText(char *string, Font* font, int fontSize);
    void setText(char* text);
    void setFont(Font* font);
    void setFontSize(int fontSize);
    void setTextColor(const UIColor& color);
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
    inline void setCallback(ButtonCallback callback){ this->callback = std::move(callback); }

    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int action) override;
    void updateMesh() override;

    bool hovered = false, pressed = false;
    QuadMeshTriplet mesh;
    Texture* texture;
    UIColorTriplet bgColor;
    UIColor fgColor;
	UIText text;
    int mode = 0;
    ButtonCallback callback;
};