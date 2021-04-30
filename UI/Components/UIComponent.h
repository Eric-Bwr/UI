#pragma once

#include <Math/Vector.h>

enum UIComponentType {
	UIIMAGE = 0,
	UIBUTTON,
	UISLIDER,
	UITEXT,
	UILAYOUT
};

class UIComponent {
public:
	int type;

	inline float getX() const { return positionX; }
	inline float getY() const { return positionY; }
	inline float getWidth() const { return width; }
	inline float getHeight() const { return height; }

	inline Vec2f getPosition() const { return Vec2f(positionX, positionY); }
	inline Vec2f getSize() const { return Vec2f(width, height); }

	virtual void setPosition(float, float) {}

	float positionX, positionY;
	float width, height;
};