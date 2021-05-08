#include "../../UIColor.h"

#include "UIScrollbar.h"

#include <iostream>

#define MAX(a, b) (a > b ? a : b)

UIScrollbar::UIScrollbar(UIComponent *_target, float width, float height)
		: UIScrollbar(_target, 0, 0, width, height) {
}

UIScrollbar::UIScrollbar(UIComponent *_target, float positionX, float positionY, float width, float height) {
	type = UIComponentType::UISCROLLBAR;
	this->target = _target;
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;
	this->barFgColor = COLOR_GREEN;
	this->barBgColor = COLOR_RED;
	orientation = Orientation::VERTICAL;
	barY = 0;
	barWidth = 6;
	barHeight = height;
	barBgMesh.load(positionX, positionY, width, height, 0);
	barFgMesh.load(positionX, positionY, width, height, 0);
	calc();
}

void UIScrollbar::calc() {
	if (orientation == Orientation::VERTICAL) {
		auto h = MAX(target->height, height);
		barHeight = height * height / h;

		if (barY <= 0)
			barY = 0;
		if (barY >= height - barHeight)
			barY = height - barHeight;

		target->setBounds(positionX, positionY - barY * (h / height), width - barWidth, h);

		barBgMesh.load(positionX + width - barWidth, positionY, barWidth, height, 0);
		barFgMesh.load(positionX + width - barWidth, positionY + barY, barWidth, barHeight, 0);
	}
}

void UIScrollbar::drag(float mx, float my) {
	float dx = mx - lastMx;
	float dy = my - lastMy;

	barY += dy;
	calc();
}

void UIScrollbar::mousePositionInput(double mx, double my) {
	hovered = mx >= positionX + width - barWidth && my >= positionY + barY &&
			mx <= positionX + width && my <= positionY + barY + barHeight;

	if (dragging)
		drag(mx, my);

	lastMx = mx;
	lastMy = my;
}

void UIScrollbar::mouseButtonInput(int button, int action) {
	if (action == INPUT_RELEASED)
		dragging = false;
	if (action == INPUT_PRESSED && hovered)
		dragging = true;
}

void UIScrollbar::setPosition(float positionX, float positionY) {
	this->positionX = positionX;
	this->positionY = positionY;
	calc();
}

void UIScrollbar::setSize(float width, float height) {
	this->width = width;
	this->height = height;
	calc();
}

void UIScrollbar::setBounds(float x, float y, float w, float h) {
	this->positionX = x;
	this->positionY = y;
	this->width = w;
	this->height = h;
	calc();
}

void UIScrollbar::setOrientation(Orientation o) {
	orientation = o;
	calc();
}

Orientation UIScrollbar::getOrientation() {
	return orientation;
}
