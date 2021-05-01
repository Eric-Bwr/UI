#pragma once

#include "Layout.h"

class FlowLayout : public Layout {
public:

	FlowLayout(float, float);

	void adjust() override;

	void setGapX(float);
	void setGapY(float);
	float getGapX() const;
	float getGapY() const;
private:
	float gapX;
	float gapY;
};
