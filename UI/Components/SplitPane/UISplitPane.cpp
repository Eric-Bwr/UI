#include "UISplitPane.h"

UISplitPane::UISplitPane(UIComponent *_left, UIComponent *_right, Orientation _orientation) {
	type = UIComponentType::UISPLITPANE;
	left = _left;
	right = _right;
	orientation = _orientation;
	divider = 0.5;
	dragging = false;
	hovered = false;
	divWidth = 4;
	dividerColor = COLOR_BLACK;
	calc();
}

void UISplitPane::calc() {
	if (left == nullptr || right == nullptr)
		return;

	float horiSplit = width * divider;
	float vertSplit = height * divider;
	float x = positionX;
	float y = positionY;


	if (orientation == Orientation::HORIZONTAL) {
		left->setBounds(x, y, horiSplit - divWidth, height);
		right->setBounds(x + horiSplit + divWidth, y, width - horiSplit - divWidth, height);
		mesh.load(x + horiSplit - divWidth, y, 2 * divWidth, height, 0);
	} else {
		left->setBounds(x, y, width, vertSplit - divWidth);
		right->setBounds(x, y + vertSplit + divWidth, width, height - vertSplit - divWidth);
		mesh.load(x, y + vertSplit - divWidth, width, 2 * divWidth, 0);
	}
}

void UISplitPane::mousePositionInput(double mx, double my) {
	float horiSplit = width * divider;
	float vertSplit = height * divider;
	if (orientation == Orientation::HORIZONTAL) {
		float x = positionX + horiSplit - divWidth;
		float y = positionY;

		hovered = mx >= x && my >= y && mx <= x + 2 * divWidth && my <= y + height;

		if (dragging) {
			divider = (mx - positionX)  / width;
			calc();
		}
	} else {
		float x = positionX;
		float y = positionY + vertSplit - divWidth;

		hovered = mx >= x && my >= y && mx <= x + width && my <= y + 2 * divWidth;

		if (dragging) {
			divider = (my - positionY)  / height;
			calc();
		}
	}
	if (left != nullptr)
		left->mousePositionInput(mx, my);
	if (right != nullptr)
		right->mousePositionInput(mx, my);
}

void UISplitPane::mouseButtonInput(int button, int action) {
	if (action == INPUT_PRESSED) {
		if (hovered)
			dragging = true;
	} else if (action == INPUT_RELEASED) {
		dragging = false;
	}

	if (left != nullptr)
		left->mouseButtonInput(button, action);
	if (right != nullptr)
		right->mouseButtonInput(button, action);
}

void UISplitPane::keyInput(int key, int action, int mods) {
	if (left != nullptr)
		left->keyInput(key, action, mods);
	if (right != nullptr)
		right->keyInput(key, action, mods);
}

void UISplitPane::charInput(unsigned int key) {
	if (left != nullptr)
		left->charInput(key);
	if (right != nullptr)
		right->charInput(key);
}

void UISplitPane::setLeft(UIComponent *_left) {
	left = _left;
	calc();
}

void UISplitPane::setRight(UIComponent *_right) {
	right = _right;
	calc();
}

void UISplitPane::setOrientation(Orientation _ori) {
	orientation = _ori;
	calc();
}

void UISplitPane::setDivider(float _divider) {
	divider = _divider;
	calc();
}

void UISplitPane::setPosition(float _x, float _y) {
	positionX = _x;
	positionY = _y;
	calc();
}

void UISplitPane::setBounds(float _x, float _y, float _w, float _h) {
	positionX = _x;
	positionY = _y;
	width = _w;
	height= _h;
	calc();
}

void UISplitPane::setSize(float _width, float _height) {
	width = _width;
	height = _height;
	calc();
}

UIComponent *UISplitPane::getLeft() {
	return left;
}

UIComponent *UISplitPane::getRight() {
	return right;
}

Orientation UISplitPane::getOrientation() {
	return orientation;
}

float UISplitPane::getDivider() {
	return divider;
}