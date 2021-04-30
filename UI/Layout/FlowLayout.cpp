#include "FlowLayout.h"

#define MAX(a, b) (a > b ? a : b)

FlowLayout::FlowLayout(float _width, float _height) : Layout(_width, _height) {
	marginX = 10;
	marginY = 10;
}

void FlowLayout::adjust() {
	float xoff = marginX;
	float yoff = marginY;
	float largestY;

	for (auto comp : components) {
		largestY = MAX(largestY, comp->height);
		if (xoff + comp->width >= width - marginX) {
			xoff = marginX;
			yoff += largestY + marginY;
		}
		comp->setPosition(xoff, yoff);
		xoff += comp->width + marginX;
	}
}

void FlowLayout::setMarginX(float m) {
	marginX = m;
}

void FlowLayout::setMarginY(float m) {
	marginY = m;
}

float FlowLayout::getMarginX() const {
	return marginX;
}

float FlowLayout::getMarginY() const {
	return marginY;
}