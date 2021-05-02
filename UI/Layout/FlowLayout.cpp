#include "FlowLayout.h"

#define MAX(a, b) (a > b ? a : b)

FlowLayout::FlowLayout(float _width, float _height) : Layout(_width, _height) {
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

void FlowLayout::setGapX(float m) {
	gapX = m;
	adjust();
}

void FlowLayout::setGapY(float m) {
	gapY = m;
	adjust();
}

float FlowLayout::getGapX() const {
	return gapX;
}

float FlowLayout::getGapY() const {
	return gapY;
}