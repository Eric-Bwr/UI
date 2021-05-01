#include "UIButton.h"

UIButton::UIButton(float positionX, float positionY, float width, float height) {
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_YELLOW;
	this->fgColor = COLOR_BLACK;
	this->hoveredColor = bgColor.darker();
	this->pressedColor = bgColor.darker().darker();
    mesh.load(positionX, positionY, width, height, 0);
}

UIButton::UIButton(float width, float height) {
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = 0;
    this->positionY = 0;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_YELLOW;
    this->fgColor = COLOR_BLACK;
	this->hoveredColor = bgColor.darker();
	this->pressedColor = bgColor.darker().darker();
    mesh.load(positionX, positionY, width, height, 0);
}

void UIButton::setTexture(Texture *texture) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, 1);
}

void UIButton::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UIButton::setSize(float width, float height) {
    this->width = width;
    this->height = height;
	mesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UIButton::mousePositionInput(double x, double y) {
	hovered = COMPONENT_HOVERED(x, y);
}

void UIButton::mouseButtonInput(int button, int action) {
    if (action == INPUT_RELEASED)
        pressed = false;
	if (!hovered)
		return;
	if (action == INPUT_PRESSED)
		pressed = true;
}
