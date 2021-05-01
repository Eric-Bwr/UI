#pragma once

#include "Layout.h"

class FlowLayout : public Layout {
public:
	float marginX;
	float marginY;

	FlowLayout(float, float);

	void adjust() override;

	void setMarginX(float);
	void setMarginY(float);
	float getMarginX() const;
	float getMarginY() const;
};
