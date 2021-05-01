#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UISlider : public UIComponent {
public:
	UISlider(float positionX, float positionY, float width, float height);
	explicit UISlider(float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
	void setPosition(float positionX, float positionY) override;
	void setSize(float width, float height);
	void mousePositionInput(double x, double y) override;
	void mouseButtonInput(int button, int action) override;

	float getMin() const;
	float getMax() const;
	float getValue() const;
	float getIncrement() const;
	bool isFloating() const;

	void setMin(float);
	void setMax(float);
	void setValue(float);
	void setIncrement(float);
	void setFloating(bool);

	bool hovered = false, dragging = false;

	float renderX = 0;

	QuadMesh bgMesh;
	QuadMesh dragMesh;

	UIColor bgColor;
	UIColor dragColor;

private:
	void drag(float);
	void update();

	float getInc(float, float);

	float min = 0;
	float max = 10;
	float value = 5;
	float increment = 1;
	bool floating = false;
};