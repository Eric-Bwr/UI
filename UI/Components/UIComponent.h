#pragma once

#include <Math/Vector.h>

#define COMPONENT_HOVERED(mx, my) (mx >= positionX && my >= positionY && \
                                   mx <= positionX + width && \
                                   my <= positionY + height)

enum UIComponentType {
	UIIMAGE = 0,
	UIBUTTON,
	UISLIDER,
	UITEXT,
    UITEXTFIELD,
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
	virtual void setBounds(float, float, float, float) {}

    virtual void keyInput(int key, int action, int mods) {}
    virtual void charInput(unsigned int key) {}
    virtual void mousePositionInput(double x, double y) {}
    virtual void mouseButtonInput(int button, int action) {}

	float positionX, positionY;
	float width, height;
};

