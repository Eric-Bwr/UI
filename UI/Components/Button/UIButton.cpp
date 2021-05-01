#include "UIButton.h"

UIButton::UIButton(float positionX, float positionY, float width, float height) {
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    bgColor = COLOR_YELLOW;
	fgColor = COLOR_BLACK;
	hoveredColor = bgColor.darker();
	pressedColor = bgColor.darker().darker();

    mesh.load(positionX, positionY, width, height, 0);
}

UIButton::UIButton(float positionX, float positionY, float width, float height, Texture *texture) {
    type = UIComponentType::UIBUTTON;
    this->texture = texture;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
	bgColor = COLOR_YELLOW;
	fgColor = COLOR_BLACK;
	hoveredColor = bgColor.darker();
	pressedColor = bgColor.darker().darker();

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

void UIButton::mousePositionInput(double mx, double my) {
	hovered = COMPONENT_HOVERED(mx, my);
}

void UIButton::mouseButtonInput(int button, int action) {

}