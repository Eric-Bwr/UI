#pragma once

#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"

class UIScrollbar: public UIComponent {
public:
	explicit UIScrollbar(UIComponent *, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, Orientation orientation=Orientation::VERTICAL);
	UIScrollbar(UIComponent *, float positionX, float positionY, float width, float height, Orientation orientation=Orientation::VERTICAL);
	void setPosition(float positionX, float positionY) override;
	void setBounds(float, float, float, float) override;
	void setSize(float width, float height);
	void mousePositionInput(double x, double y) override;
	void mouseButtonInput(int button, int action) override;

	UIComponent *target;
	QuadMesh barBgMesh;
	QuadMesh barFgMesh;
	UIColor barFgColor;
	UIColor barBgColor;
	float barWidth;

	Orientation orientation;
private:
	void calc();
	void drag(float, float);

	float barY;
	float barHeight;

	bool dragging = false, hovered = false;

	float lastMx;
	float lastMy;
};