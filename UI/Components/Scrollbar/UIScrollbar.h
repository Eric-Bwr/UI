#pragma once

#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"

class UIScrollbar: public UIComponent {
public:
	explicit UIScrollbar(UIComponent *, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
	UIScrollbar(UIComponent *, float positionX, float positionY, float width, float height);
	void setPosition(float positionX, float positionY) override;
	void setBounds(float, float, float, float) override;
	void setSize(float width, float height);
	void mousePositionInput(double x, double y) override;
	void mouseButtonInput(int button, int action) override;

	Orientation getOrientation();
	void setOrientation(Orientation);

	UIComponent *target;
	QuadMesh barBgMesh;
	QuadMesh barFgMesh;
	UIColor barFgColor;
	UIColor barBgColor;
private:
	void calc();
	void drag(float, float);

	Orientation orientation;
	float barY;
	float barWidth;
	float barHeight;

	bool dragging, hovered;

	float lastMx;
	float lastMy;
};