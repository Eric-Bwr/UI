#pragma once

#include "Layout.h"

class FlowLayout : public Layout {
public:
	void init(float width, float height);

	void adjust() override;

	void setGapX(float gapX);
	void setGapY(float gapY);

	float getGapX() { return gapX ;}
	float getGapY() { return gapY ;}

    float gapX;
    float gapY;
};