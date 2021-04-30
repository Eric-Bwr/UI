#include "BoxLayout.h"

BoxLayout::BoxLayout(float _width, float _height, LayoutDirection dir) : Layout(_width, _height) {
	direction = dir;
	margin = 10;
}

void BoxLayout::adjust() {
	float off = margin;
	if (direction == LayoutDirection::ROW) {
		for (auto comp : components) {
			comp->setPosition(width / 2 - comp->width / 2, off);
			off += comp->height + margin;
		}
	} else if (direction == LayoutDirection::COLUMN) {
		for (auto comp : components) {
			comp->setPosition(off, height / 2 - comp->height / 2);
			off += comp->width + margin;
		}
	} else {
		/* Illegal Layout Direction */
	}
}

void BoxLayout::setMargin(float m) {
	margin = m;
}

float BoxLayout::getMargin() const {
	return margin;
}

void BoxLayout::setDirection(LayoutDirection ld) {
	direction = ld;
}

LayoutDirection BoxLayout::getDirection() const {
	return direction;
}