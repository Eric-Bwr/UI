#include "UIButton.h"

UIButton::UIButton(float positionX, float positionY, float width, float height) {
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    mesh.load(positionX, positionY, width, height, 0);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

UIButton::UIButton(float positionX, float positionY, float width, float height, Texture *texture) {
    type = UIComponentType::UIBUTTON;
    this->texture = texture;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    mesh.load(positionX, positionY, width, height, 1);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
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