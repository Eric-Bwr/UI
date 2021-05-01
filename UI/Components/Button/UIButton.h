#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UIButton : public UIComponent {
public:
    UIButton(float positionX, float positionY, float width, float height);
    UIButton(float positionX, float positionY, float width, float height, Texture* texture);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int button, int action) override;
    bool hovered, pressed;
    QuadMesh mesh;
    Texture* texture;
    UIColor bgColor;
	UIColor fgColor;
	UIColor hoveredColor;
	UIColor pressedColor;
};