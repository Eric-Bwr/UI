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
    void setTexture(Texture* texture);
    void setBackgroundColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor);
    void setBackgroundCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setSlideColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor);
    void setSlideCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setDragColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor);
    void setDragCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
	void setSize(float width, float height);
	void setBounds(float, float, float, float) override;
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
	void mousePositionInput(double x, double y) override;
	void mouseButtonInput(int button, int action) override;
	inline float getMin() { return min; }
	inline float getMax() { return max; }
	inline float getValue() { return value; }
	inline float getIncrement() { return increment; }
	inline bool isFloating() { return floating; }
	void setMin(float min);
	void setMax(float max);
	void setValue(float value);
	inline void setIncrement(float increment){ this->increment = increment; }
	inline void setFloating(bool floating){ this->floating = floating; }
	bool hovered = false, dragging = false;
	Texture* texture;
    QuadMeshTriplet dragMesh;
    QuadMeshTriplet slideMesh;
    QuadMeshTriplet bgMesh;
	UIColorTriplet bgColor;
	UIColorTriplet slideColor;
	UIColorTriplet dragColor;
private:
	void drag(float x);
	void update();
	void updateBackgroundMesh();
    void updateSlideMesh();
    void updateDragMesh();
	float getInc(float value) const;
	float min;
	float max;
	float value;
	float increment = 1;
    float renderX = 0, renderWidth;
	bool floating = false;
	float sizes[18];
	int modes[3];
};