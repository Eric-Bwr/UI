#include "UIButton.h"

void UIButton::init(float positionX, float positionY, float width, float height){
    this->mesh.init();
    this->text.init("", 10, positionX, positionY, width, height, UITextMode::CENTERED);
    type = UIComponentType::UIBUTTON;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor.standard = COLOR_RED;
    this->bgColor.hover = COLOR_RED.darker();
    this->bgColor.pressed = COLOR_RED.darker().darker();
    this->fgColor = COLOR_WHITE;
    mesh.load(positionX, positionY, width, height, 0);
    this->update = true;
}

void UIButton::init(char *text, Font *font, int fontSize, int mode, float positionX, float positionY, float width, float height) {
    init(positionX, positionY, width, height);
    this->text.mode = mode;
    this->text.setText(text);
    this->text.setFont(font);
    this->text.setFontSize(fontSize);
}

void UIButton::setBackgroundColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor) {
    this->bgColor.standard = standardColor;
    this->bgColor.hover = hoverColor;
    this->bgColor.pressed = pressedColor;
    if (mode == 0)
        mode = 1;
    else if (mode == 2)
        mode = 3;
    mesh.loadPosition(positionX, positionY, width, height, mode);
    this->update = true;
}

void UIButton::setBackgroundTexture(Texture *texture) {
    this->texture = texture;
    if(texture == nullptr) {
        if (mode == 3)
            mode = 1;
        else if (mode == 2)
            mode = 0;
    }else {
        if (mode == 0)
            mode = 2;
        else if (mode == 1)
            mode = 3;
    }
    mesh.loadPosition(positionX, positionY, width, height, mode);
    this->update = true;
}

void UIButton::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
    this->texture = texture;
    if(texture == nullptr) {
        if (mode == 3)
            mode = 1;
        else if (mode == 2)
            mode = 0;
    }else {
        if (mode == 0)
            mode = 2;
        else if (mode == 1)
            mode = 3;
    }
    mesh.load(positionX, positionY, width, height, mode, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, buttonX, buttonY, buttonWidth, buttonHeight, buttonX, buttonY, buttonWidth, buttonHeight);
    this->update = true;
}

void UIButton::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    if(texture == nullptr) {
        if (mode == 3)
            mode = 1;
        else if (mode == 2)
            mode = 0;
    }else {
        if (mode == 0)
            mode = 2;
        else if (mode == 1)
            mode = 3;
    }
    mesh.load(positionX, positionY, width, height, mode, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, hoverX, hoverY, hoverWidth, hoverHeight, pressedX, pressedY, pressedWidth, pressedHeight);
    this->update = true;
}

void UIButton::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX, positionY);
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UIButton::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UIButton::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x, y, w, h);
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UIButton::setText(char *string, Font *font, int fontSize) {
    text.text = string;
    text.font = font;
    text.positionX = positionX;
    text.positionY = positionY;
    text.setFontSize(fontSize);
    this->update = true;
}

void UIButton::setText(char *string) {
    text.setText(string);
    this->update = true;
}

void UIButton::setFont(Font *font) {
    text.setFont(font);
    this->update = true;
}

void UIButton::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
    this->update = true;
}

void UIButton::setTextColor(const UIColor& color) {
    this->fgColor = color;
}

void UIButton::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    mesh.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    this->update = true;
}

void UIButton::mousePositionInput(double x, double y) {
    bool previous = hovered;
    hovered = COMPONENT_HOVERED(x, y);
    if (previous && !hovered || !previous && hovered)
        if (callback != nullptr)
            callback(pressed, hovered);
}

void UIButton::mouseButtonInput(int action) {
    bool previous = pressed;
    if (action == INPUT_PRESSED) {
        if (hovered)
            pressed = true;
    } else if (action == INPUT_RELEASED)
        pressed = false;
    if (callback != nullptr)
        if (previous && !pressed || !previous && pressed)
            callback(pressed, hovered);
}

void UIButton::updateMesh() {
    mesh.updateMesh();
    text.updateMesh();
}
