#include "UITextField.h"

UITextField::UITextField(float positionX, float positionY, float width, float height) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_YELLOW;
    this->fgColor = COLOR_BLACK;
    mesh.load(positionX, positionY, width, height, 0);
}

UITextField::UITextField(float positionX, float positionY, float width, float height, Texture *texture) {
    type = UIComponentType::UITEXTFIELD;
    this->texture = texture;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    mesh.load(positionX, positionY, width, height, 1);
    this->bgColor = COLOR_YELLOW;
    this->fgColor = COLOR_BLACK;
}

void UITextField::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UITextField::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
}
#include "iostream"
void UITextField::mousePositionInput(double x, double y) {
    std::cout << x << " TEXTFIELD " << y << "\n";
}

void UITextField::mouseButtonInput(int button, int action) {

}