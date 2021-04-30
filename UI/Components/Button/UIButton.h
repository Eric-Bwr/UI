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
    QuadMesh mesh;
    Texture* texture;
    UIColor bgColor;
	UIColor fgColor;
};