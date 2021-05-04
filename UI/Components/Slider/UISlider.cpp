#include "UISlider.h"

#include <iostream>

UISlider::UISlider(float positionX, float positionY, float width, float height) {
    type = UIComponentType::UISLIDER;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_BLUE;
	this->dragColor = COLOR_RED;
	update();

    bgMesh.load(positionX, positionY, width, height, 0);
    dragMesh.load(positionX, positionY, renderX, height, 0);
}

UISlider::UISlider(float width, float height) {
    type = UIComponentType::UISLIDER;
    this->positionX = 0;
    this->positionY = 0;
    this->width = width;
    this->height = height;
	this->bgColor = COLOR_BLUE;
	this->dragColor = COLOR_RED;
	update();

	bgMesh.load(positionX, positionY, width, height, 0);
	dragMesh.load(positionX, positionY, renderX, height, 0);
}

void UISlider::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;

	bgMesh.load(positionX, positionY, width, height, 0);
	dragMesh.load(positionX, positionY, renderX, height, 0);
}

void UISlider::setSize(float width, float height) {
    this->width = width;
    this->height = height;
	bgMesh.load(positionX, positionY, width, height, 0);
	dragMesh.load(positionX, positionY, renderX, height, 0);
}

void UISlider::setBounds(float x, float y, float w, float h) {
	this->positionX = x;
	this->positionY = y;
	this->width = w;
	this->height = h;

	bgMesh.load(positionX, positionY, width, height, 0);
	dragMesh.load(positionX, positionY, renderX, height, 0);
}


void UISlider::mousePositionInput(double x, double y) {
	hovered = COMPONENT_HOVERED(x, y);
	if (dragging) {
		drag(x - positionX);
	}
}

void UISlider::mouseButtonInput(int button, int action) {
    if (button == MOUSE_BUTTON_PRESSED && action == INPUT_PRESSED) {
        if (hovered)
            dragging = true;
    } else if (button == MOUSE_BUTTON_PRESSED && action == INPUT_RELEASED)
        dragging = false;
}

void UISlider::drag(float rx) {
	if (!hovered)
		return;

//	renderX = rx;

	float norm = rx / width;
	value = getInc(min + (max - min) * norm, increment);

	float vnorm = (value - min) / (max - min);
	renderX = getInc(width * vnorm, increment);

	bgMesh.load(positionX, positionY, width, height, 0);
	dragMesh.load(positionX, positionY, renderX, height, 0);
}


float UISlider::getInc(float val, float inc) {
	if (floating)
		return val;
	float one = 1.0f / inc;
	return std::round(val * one) / one;
}

void UISlider::update() {
	float norm = (value - min) / (max - min);
	renderX = width * norm;
}

float UISlider::getMin() const {
	return min;
}

float UISlider::getMax() const {
	return max;
}

float UISlider::getValue() const {
	return value;
}

float UISlider::getIncrement() const {
	return increment;
}

bool UISlider::isFloating() const {
	return floating;
}

void UISlider::setMin(float m) {
	min = m;
	update();
}

void UISlider::setMax(float m) {
	max = m;
	update();
}

void UISlider::setValue(float v) {
	value = v;
	update();
}

void UISlider::setIncrement(float inc) {
	increment = inc;
}

void UISlider::setFloating(bool f) {
	floating = f;
}
