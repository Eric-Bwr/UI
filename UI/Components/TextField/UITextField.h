#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UITextField : public UIComponent {
public:
    explicit UITextField(float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    UITextField(float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    void setTexture(Texture* texture);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
	void setBounds(float, float, float, float) override;
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int button, int action) override;
    QuadMesh mesh;
    Texture* texture;
    UIColor bgColor;
    UIColor fgColor;
};
