#include "UIButton.h"

UIButton::UIButton(float positionX, float positionY, float width, float height)
        : text("", 0, positionX, positionY, width, height, UITextMode::CENTERED) {
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_WHITE;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    mesh.load(positionX, positionY, width, height, 0);
    hoverMesh.load(positionX, positionY, width, height, 0);
    pressedMesh.load(positionX, positionY, width, height, 0);
}

UIButton::UIButton(float width, float height)
        : text("", 0, 0, 0, width, height, UITextMode::CENTERED) {
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = 0;
    this->positionY = 0;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_WHITE;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    mesh.load(positionX, positionY, width, height, 0);
    hoverMesh.load(positionX, positionY, width, height, 0);
    pressedMesh.load(positionX, positionY, width, height, 0);
}

void UIButton::setTexture(Texture *texture) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    hoverMesh.load(positionX, positionY, width, height, texture != nullptr);
    pressedMesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UIButton::setTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, texture != nullptr);
    hoverMesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), hoverX, hoverY, hoverWidth, hoverHeight, texture != nullptr);
    pressedMesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), pressedX, pressedY, pressedWidth, pressedHeight, texture != nullptr);
}

void UIButton::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX, positionY);
    mesh.loadPosition(positionX, positionY, width, height);
    hoverMesh.loadPosition(positionX, positionY, width, height);
    pressedMesh.loadPosition(positionX, positionY, width, height);
}

void UIButton::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.loadPosition(positionX, positionY, width, height);
    hoverMesh.loadPosition(positionX, positionY, width, height);
    pressedMesh.loadPosition(positionX, positionY, width, height);
}

void UIButton::setBounds(float x, float y, float w, float h) {
	this->positionX = x;
	this->positionY = y;
	this->width = w;
	this->height = h;
	text.setBounds(x, y, w, h);
    mesh.loadPosition(positionX, positionY, width, height);
    hoverMesh.loadPosition(positionX, positionY, width, height);
    pressedMesh.loadPosition(positionX, positionY, width, height);
}

void UIButton::setText(const char *string, Font *font, int fontSize) {
    text.text = string;
    text.font = font;
    text.positionX = positionX;
    text.positionY = positionY;
    text.setFontSize(fontSize);
}

void UIButton::setText(const char *string) {
    text.setText(string);
}

void UIButton::setFont(Font *font) {
    text.setFont(font);
}

void UIButton::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
}

void UIButton::mousePositionInput(double x, double y) {
    hovered = COMPONENT_HOVERED(x, y);
}

void UIButton::mouseButtonInput(int button, int action) {
    if (button == MOUSE_BUTTON_PRESSED && action == INPUT_PRESSED) {
        if (hovered)
            pressed = true;
    } else if (button == MOUSE_BUTTON_PRESSED && action == INPUT_RELEASED)
        pressed = false;
}
