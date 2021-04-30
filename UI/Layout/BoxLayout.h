#pragma once

#include "Layout.h"

class BoxLayout: public Layout {
public:
	float margin;
	LayoutDirection direction;

	BoxLayout(float, float, LayoutDirection dir=LayoutDirection::ROW);

	void adjust() override;

	void setMargin(float);
	float getMargin() const;

	void setDirection(LayoutDirection);
	LayoutDirection getDirection() const;
};