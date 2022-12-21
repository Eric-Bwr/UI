#include "FlowLayout.h"

#define MAX(a, b) (a > b ? a : b)

void FlowLayout::init(float width, float height) {
    initLayout(width, height);
    gapX = 10;
    gapY = 10;
}

void FlowLayout::adjust() {
	float xoff = insets.left;
	float yoff = insets.top;
	float largestY;

	for (auto comp : components) {
		largestY = MAX(largestY, comp->height);
		if (xoff + comp->width >= width - gapX) {
			xoff = gapX;
			yoff += largestY + gapY;
		}
		comp->setPosition(xoff, yoff);
		xoff += comp->width + gapX;
	}
}

void FlowLayout::setGapX(float gapX) {
	this->gapX = gapX;
	adjust();
}

void FlowLayout::setGapY(float gapY) {
	this->gapY = gapY;
	adjust();
}