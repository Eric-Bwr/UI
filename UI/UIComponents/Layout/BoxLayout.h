#pragma once

#include "Layout.h"

class BoxLayout : public Layout {
public:
    void init(float width, float height, LayoutDirection dir = LayoutDirection::ROW);

    void adjust() override;

    void setGap(float gap);
    void setDirection(LayoutDirection direction);

    float getGap() { return gap; }
    LayoutDirection getDirection() { return direction; }

    float gap;
    LayoutDirection direction;
};