#pragma once

#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"

class UIScrollbar: public UIComponent {
public:
	void init(UIComponent * target, float positionX = 0.0f, float positionY = 0.0f,
              float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, Orientation orientation = Orientation::VERTICAL);

	void setPosition(float positionX, float positionY) override;
	void setBounds(float positionX, float positionY, float width, float height) override;
	void setSize(float width, float height);
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);

    void mousePositionInput(double x, double y) override;
	void mouseButtonInput(int action) override;
    void updateMesh() override;

	UIComponent *target;
	QuadMesh barBgMesh;
	QuadMesh barFgMesh;
	UIColor barFgColor;
	UIColor barBgColor;
	Orientation orientation;
    float barWidth;
	void calc();
	void drag(float mx, float my);
	float barY, barHeight;
	bool dragging = false, hovered = false;
	float lastMx, lastMy;
};