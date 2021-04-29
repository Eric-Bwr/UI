#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UIButton : public UIComponent, public UIColor {
public:
    UIButton(float positionX, float positionY, float width, float height);
    UIButton(float positionX, float positionY, float width, float height, Texture* texture);
    void setPosition(float positionX, float positionY);
    void setSize(float width, float height);
    QuadMesh mesh;
    Texture* texture;
};