#include "BoxLayout.h"

BoxLayout::BoxLayout(float _width, float _height, LayoutDirection dir) : Layout(_width, _height) {
	direction = dir;
	gap = 10;
}

void BoxLayout::adjust() {
	if (direction == LayoutDirection::ROW) {
		float off = insets.top;
		for (auto comp : components) {
			comp->setPosition(width / 2 - comp->width / 2, off);
			off += comp->height + gap;
		}
	} else if (direction == LayoutDirection::COLUMN) {
		float off = insets.left;
		for (auto comp : components) {
			comp->setPosition(off, height / 2 - comp->height / 2);
			off += comp->width + gap;
		}
	}
}

void BoxLayout::setGap(float m) {
	gap = m;
	adjust();
}

float BoxLayout::getGap() const {
	return gap;
}

void BoxLayout::setDirection(LayoutDirection ld) {
	direction = ld;
	adjust();
}

LayoutDirection BoxLayout::getDirection() const {
	return direction;
}