#include "UISlider.h"

UISlider::UISlider(float width, float height)
        : UISlider(0, 0, width, height, 0, 0, 10) {}

UISlider::UISlider(float positionX, float positionY, float width, float height)
        : UISlider(positionX, positionY, width, height, 0, 0, 10) {}

UISlider::UISlider(float positionX, float positionY, float width, float height, float value, float min, float max) {
    type = UIComponentType::UISLIDER;
    this->value = value;
    this->min = min;
    this->max = max;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_BLUE;
    this->slideColor = COLOR_RED;
    this->dragColor = COLOR_RED;
    this->renderWidth = width;
    update();
    for (int i = 0; i < 18; i++)
        sizes[i] = 0;
    bgMesh.load(positionX, positionY, width, height, 0);
    slideMesh.load(0, 0, 0, 0, 0);
    dragMesh.load(0, 0, 0, 0, 0);
}

void UISlider::setTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    bgMesh.load(positionX, positionY, width, height, texture != nullptr, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, hoverX, hoverY, hoverWidth, hoverHeight, pressedX, pressedY, pressedWidth, pressedHeight);
}

void UISlider::setSlideCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    sizes[6] = buttonX;
    sizes[7] = buttonY;
    sizes[8] = buttonWidth;
    sizes[9] = buttonHeight;
    sizes[10] = hoverX;
    sizes[11] = hoverY;
    sizes[12] = hoverWidth;
    sizes[13] = hoverHeight;
    sizes[14] = pressedX;
    sizes[15] = pressedY;
    sizes[16] = pressedWidth;
    sizes[17] = pressedHeight;
    slideMesh.load(positionX, positionY, renderX + sizes[0] / 2, height, texture != nullptr, texture->getWidth(), texture->getHeight(), sizes[6], sizes[7], ((renderX + sizes[0] / 2) / width) * sizes[8], sizes[9], sizes[10], sizes[11], ((renderX + sizes[0] / 2) / width) * sizes[12], sizes[13], sizes[14], sizes[15], ((renderX + sizes[0] / 2) / width) * sizes[16], sizes[17]);
}

void UISlider::setDragCoords(float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    sizes[0] = buttonWidth;
    sizes[1] = buttonHeight;
    sizes[2] = hoverWidth;
    sizes[3] = hoverHeight;
    sizes[4] = pressedWidth;
    sizes[5] = pressedHeight;
    renderWidth = width - sizes[0];
    dragMesh.load(positionX + renderX, positionY + height / 2 - sizes[1] / 2, sizes[0], sizes[1], positionX + renderX, positionY + height / 2 - sizes[3] / 2, sizes[2], sizes[3], positionX + renderX, positionY + height / 2 - sizes[5] / 2, sizes[4], sizes[5], texture != nullptr, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, hoverX, hoverY, hoverWidth, hoverHeight, pressedX, pressedY, pressedWidth, pressedHeight);
    slideMesh.load(positionX, positionY, renderX + sizes[0] / 2, height, texture != nullptr, texture->getWidth(), texture->getHeight(), sizes[6], sizes[7], ((renderX + sizes[0] / 2) / width) * sizes[8], sizes[9], sizes[10], sizes[11], ((renderX + sizes[0] / 2) / width) * sizes[12], sizes[13], sizes[14], sizes[15], ((renderX + sizes[0] / 2) / width) * sizes[16], sizes[17]);
}

void UISlider::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    bgMesh.loadPosition(positionX, positionY, width, height);
    slideMesh.load(positionX, positionY, renderX + sizes[0] / 2, height, texture != nullptr, texture->getWidth(), texture->getHeight(), sizes[6], sizes[7], ((renderX + sizes[0] / 2) / width) * sizes[8], sizes[9], sizes[10], sizes[11], ((renderX + sizes[0] / 2) / width) * sizes[12], sizes[13], sizes[14], sizes[15], ((renderX + sizes[0] / 2) / width) * sizes[16], sizes[17]);
    dragMesh.loadPosition(positionX + renderX, positionY + height / 2 - sizes[1] / 2, sizes[0], sizes[1], positionX + renderX, positionY + height / 2 - sizes[3] / 2, sizes[2], sizes[3], positionX + renderX, positionY + height / 2 - sizes[5] / 2, sizes[4], sizes[5]);
}

void UISlider::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    bgMesh.loadPosition(positionX, positionY, width, height);
    slideMesh.load(positionX, positionY, renderX + sizes[0] / 2, height, texture != nullptr, texture->getWidth(), texture->getHeight(), sizes[6], sizes[7], ((renderX + sizes[0] / 2) / width) * sizes[8], sizes[9], sizes[10], sizes[11], ((renderX + sizes[0] / 2) / width) * sizes[12], sizes[13], sizes[14], sizes[15], ((renderX + sizes[0] / 2) / width) * sizes[16], sizes[17]);
}

void UISlider::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    bgMesh.loadPosition(positionX, positionY, width, height);
    slideMesh.load(positionX, positionY, renderX + sizes[0] / 2, height, texture != nullptr, texture->getWidth(), texture->getHeight(), sizes[6], sizes[7], ((renderX + sizes[0] / 2) / width) * sizes[8], sizes[9], sizes[10], sizes[11], ((renderX + sizes[0] / 2) / width) * sizes[12], sizes[13], sizes[14], sizes[15], ((renderX + sizes[0] / 2) / width) * sizes[16], sizes[17]);
}

void UISlider::mousePositionInput(double x, double y) {
    hovered = COMPONENT_HOVERED(x, y);
    if (dragging)
        drag(x - positionX - sizes[0] / 2);
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
    value = getInc(min + (max - min) * (rx / renderWidth));
    if (value > max)
        value = max;
    else if (value < min)
        value = min;
    renderX = getInc(renderWidth * (value - min) / (max - min));
    slideMesh.load(positionX, positionY, renderX + sizes[0] / 2, height, texture != nullptr, texture->getWidth(), texture->getHeight(), sizes[6], sizes[7], ((renderX + sizes[0] / 2) / width) * sizes[8], sizes[9], sizes[10], sizes[11], ((renderX + sizes[0] / 2) / width) * sizes[12], sizes[13], sizes[14], sizes[15], ((renderX + sizes[0] / 2) / width) * sizes[16], sizes[17]);
    dragMesh.loadPosition(positionX + renderX, positionY + height / 2 - sizes[1] / 2, sizes[0], sizes[1], positionX + renderX, positionY + height / 2 - sizes[3] / 2, sizes[2], sizes[3], positionX + renderX, positionY + height / 2 - sizes[5] / 2, sizes[4], sizes[5]);
}

float UISlider::getInc(float val) const {
    if (floating)
        return val;
    float one = 1.0f / increment;
    return std::round(val * one) / one;
}

void UISlider::update() {
    float norm = (value - min) / (max - min);
    renderX = renderWidth * norm;
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