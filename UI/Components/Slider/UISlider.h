#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UISlider : public UIComponent {
public:
	UISlider(float positionX, float positionY, float width, float height);
	explicit UISlider(float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
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
	void drag(float);
	void update();
	float getInc(float, float) const;
	float min = 0;
	float max = 10;
	float value = 5;
	float increment = 1;
    float renderX = 0;
	bool floating = false;
	float sizes[18];
};