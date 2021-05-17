#include "UISplitPane.h"

UISplitPane::UISplitPane(UIComponent *left, UIComponent *right, Orientation orientation) {
	type = UIComponentType::UISPLITPANE;
	this->left = left;
    this->right = right;
	this->orientation = orientation;
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

void UISplitPane::mouseButtonInput(int action) {
	if (action == INPUT_PRESSED) {
		if (hovered)
			dragging = true;
	} else if (action == INPUT_RELEASED) {
		dragging = false;
	}

	if (left != nullptr)
		left->mouseButtonInput(action);
	if (right != nullptr)
		right->mouseButtonInput(action);
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

void UISplitPane::setLeft(UIComponent *left) {
    this->left = left;
	calc();
}

void UISplitPane::setRight(UIComponent *right) {
    this->right = right;
	calc();
}

void UISplitPane::setOrientation(Orientation ori) {
    this->orientation = ori;
	calc();
}

void UISplitPane::setDivider(float divider) {
    this->divider = divider;
	calc();
}

void UISplitPane::setPosition(float x, float y) {
	this->positionX = x;
	this->positionY = y;
	calc();
}

void UISplitPane::setBounds(float positionX, float positionY, float width, float height) {
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;
	calc();
}

void UISplitPane::setSize(float width, float height) {
	this->width = width;
	this->height = height;
	calc();
}