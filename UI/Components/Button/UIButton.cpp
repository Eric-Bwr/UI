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
    mesh.load(positionX, positionY, width, height, 0);
}

UIButton::UIButton(float positionX, float positionY, float width, float height, Texture *texture) {
    type = UIComponentType::UIBUTTON;
    this->texture = texture;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    mesh.load(positionX, positionY, width, height, 1);
	this->bgColor = COLOR_YELLOW;
	this->fgColor = COLOR_BLACK;
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

}

void UIButton::mouseButtonInput(int button, int action) {

}