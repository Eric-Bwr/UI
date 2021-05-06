#include "UISlider.h"

UISlider::UISlider(float width, float height)
        : UISlider(0, 0, width, height) {}

UISlider::UISlider(float positionX, float positionY, float width, float height) {
    type = UIComponentType::UISLIDER;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_BLUE;
    this->dragColor = COLOR_RED;
    update();
    dragMesh.load(positionX, positionY, renderX, height, 0);
    dragHoverMesh.load(positionX, positionY, renderX, height, 0);
    dragPressedMesh.load(positionX, positionY, renderX, height, 0);
    bgMesh.load(positionX, positionY, width, height, 0);
    bgHoverMesh.load(positionX, positionY, width, height, 0);
    bgPressedMesh.load(positionX, positionY, width, height, 0);
}

void UISlider::setTexture(Texture *texture) {
    this->texture = texture;
    dragMesh.load(positionX, positionY, renderX, height, texture != nullptr);
    dragHoverMesh.load(positionX, positionY, renderX, height, texture != nullptr);
    dragPressedMesh.load(positionX, positionY, renderX, height, texture != nullptr);
    bgMesh.load(positionX, positionY, width, height, texture != nullptr);
    bgHoverMesh.load(positionX, positionY, width, height, texture != nullptr);
    bgPressedMesh.load(positionX, positionY, width, height, texture != nullptr);
}
/*
void UISlider::setTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    dragMesh.load(positionX, positionY, renderX, height, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, texture != nullptr);
    dragHoverMesh.load(positionX, positionY, renderX, height, texture->getWidth(), texture->getHeight(), hoverX, hoverY, hoverWidth, hoverHeight, texture != nullptr);
    dragPressedMesh.load(positionX, positionY, renderX, height, texture->getWidth(), texture->getHeight(), pressedX, pressedY, pressedWidth, pressedHeight, texture != nullptr);
}

void UISlider::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    bgMesh.load(positionX, positionY, renderX, height, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, texture != nullptr);
    bgHoverMesh.load(positionX, positionY, renderX, height, texture->getWidth(), texture->getHeight(), hoverX, hoverY, hoverWidth, hoverHeight, texture != nullptr);
    bgPressedMesh.load(positionX, positionY, renderX, height, texture->getWidth(), texture->getHeight(), pressedX, pressedY, pressedWidth, pressedHeight, texture != nullptr);
}
*/
void UISlider::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    dragMesh.loadPosition(positionX, positionY, renderX, height);
    dragHoverMesh.loadPosition(positionX, positionY, renderX, height);
    dragPressedMesh.loadPosition(positionX, positionY, renderX, height);
    bgMesh.loadPosition(positionX, positionY, width, height);
    bgHoverMesh.loadPosition(positionX, positionY, width, height);
    bgPressedMesh.loadPosition(positionX, positionY, width, height);
}

void UISlider::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    dragMesh.loadPosition(positionX, positionY, renderX, height);
    dragHoverMesh.loadPosition(positionX, positionY, renderX, height);
    dragPressedMesh.loadPosition(positionX, positionY, renderX, height);
    bgMesh.loadPosition(positionX, positionY, width, height);
    bgHoverMesh.loadPosition(positionX, positionY, width, height);
    bgPressedMesh.loadPosition(positionX, positionY, width, height);
}

void UISlider::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    dragMesh.loadPosition(positionX, positionY, renderX, height);
    dragHoverMesh.loadPosition(positionX, positionY, renderX, height);
    dragPressedMesh.loadPosition(positionX, positionY, renderX, height);
    bgMesh.loadPosition(positionX, positionY, width, height);
    bgHoverMesh.loadPosition(positionX, positionY, width, height);
    bgPressedMesh.loadPosition(positionX, positionY, width, height);
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

//TODO:	renderX = rx;

    float norm = rx / width;
    value = getInc(min + (max - min) * norm, increment);

    float vnorm = (value - min) / (max - min);
    renderX = getInc(width * vnorm, increment);

    dragMesh.loadPosition(positionX, positionY, renderX, height);
    dragHoverMesh.loadPosition(positionX, positionY, renderX, height);
    dragPressedMesh.loadPosition(positionX, positionY, renderX, height);
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