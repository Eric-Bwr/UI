#pragma once

#include <Math/Vector.h>
#include <Math/Matrix.h>

enum UIComponentType {
	UIIMAGE = 0,
	UIBUTTON,
	UISLIDER,
	UITEXT,
};

class UIComponent {
public:
	int type;

	void setPosition(float x, float y);
	void setPosition(Vec2f vec);

	void setSize(float width, float height);

	inline float getX() { return x; }
	inline float getY() { return y; }
	inline float getWidth() { return width; }
	inline float getHeight() { return height; }

	inline Vec2f getPosition() { return Vec2f(x, y); }
private:
	float x, y;
	float width, height;

	Mat4f modelMatrix;

	void updateModelMatrix();
};