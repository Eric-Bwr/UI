#include "UITextField.h"

UITextField::UITextField(float width, float height) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->positionX = 0;
    this->positionY = 0;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_YELLOW;
    this->fgColor = COLOR_BLACK;
    mesh.load(positionX, positionY, width, height, 0);
}

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

void UITextField::setTexture(Texture* texture) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, 1);
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
