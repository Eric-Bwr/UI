#pragma once

#include "Layout.h"

class BorderLayout : public Layout {
public:

	BorderLayout(float, float);

	void adjust() override;

	void add(UIComponent *) override;
	void add(UIComponent *, LayoutPosition) override;

	void setGapX(float);
	void setGapY(float);
	float getGapX() const;
	float getGapY() const;

private:
	float gapX;
	float gapY;

	UIComponent *east = nullptr;
	UIComponent *north = nullptr;
	UIComponent *west = nullptr;
	UIComponent *south = nullptr;
	UIComponent *center = nullptr;
};
