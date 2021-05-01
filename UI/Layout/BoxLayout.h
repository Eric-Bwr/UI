#pragma once

#include "Layout.h"

class BoxLayout : public Layout {
public:
    LayoutDirection direction;

    BoxLayout(float, float, LayoutDirection dir = LayoutDirection::ROW);

    void adjust() override;

    void setGap(float);

    float getGap() const;

    void setDirection(LayoutDirection);

    LayoutDirection getDirection() const;

private:
	float gap;
};