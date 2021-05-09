#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UISlider : public UIComponent {
public:
    explicit UISlider(float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    UISlider(float positionX, float positionY, float width, float height);
	UISlider(float positionX, float positionY, float width, float height, float value, float min, float max);
    void setTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setSlideCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setDragCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
	void setSize(float width, float height);
	void setBounds(float, float, float, float) override;
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
	Texture* texture;
    QuadMeshTriplet dragMesh;
    QuadMeshTriplet slideMesh;
    QuadMeshTriplet bgMesh;
	UIColor bgColor;
	UIColor slideColor;
	UIColor dragColor;
private:
	void drag(float x);
	void update();
	float getInc(float value) const;
	float min;
	float max;
	float value;
	float increment = 1;
    float renderX = 0, renderWidth;
	bool floating = false;
	float sizes[18];
};