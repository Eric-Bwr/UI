#include "BorderLayout.h"

#include <iostream>

BorderLayout::BorderLayout(float _width, float _height) : Layout(_width, _height) {
	gapX = 10;
	gapY = 10;
}

void BorderLayout::adjust() {
	float top = insets.top;
	float bottom = height - insets.bottom;
	float left = insets.left;
	float right = width - insets.right;

	if (north != nullptr) {
		north->setBounds(left, top, right - left, north->height);
		top += north->height + gapY;
	}

	if (south != nullptr) {
		south->setBounds(left, bottom - south->height, right - left, south->height);
		bottom -= south->height + gapY;
	}

	if (east != nullptr) {
		east->setBounds(right - east->width, top, east->width, bottom - top);
		right -= east->width + gapX;
	}

	if (west != nullptr) {
		west->setBounds(left, top, west->width, bottom - top);
		left += west->width + gapX;
	}

	if (center != nullptr)
		center->setBounds(left, top, right - left, bottom - top);
}

void BorderLayout::add(UIComponent *c) {
	add(c, LayoutPosition::CENTER);
}

void BorderLayout::add(UIComponent *c, LayoutPosition pos) {
	switch (pos) {
	case LayoutPosition::CENTER:
		center = c;
		break;
	case LayoutPosition::NORTH:
		north = c;
		break;
	case LayoutPosition::SOUTH:
		south = c;
		break;
	case LayoutPosition::EAST:
		east = c;
		break;
	case LayoutPosition::WEST:
		west = c;
		break;
	}
	components.push_back(c);
	adjust();
}

void BorderLayout::setGapX(float m) {
	gapX = m;
	adjust();
}

void BorderLayout::setGapY(float m) {
	gapY = m;
	adjust();
}

float BorderLayout::getGapX() const {
	return gapX;
}

float BorderLayout::getGapY() const {
	return gapY;
}