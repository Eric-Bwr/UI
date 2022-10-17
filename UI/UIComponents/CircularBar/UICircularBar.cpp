#include "UICircularBar.h"

UICircularBar::UICircularBar(float width, float height)
        : UICircularBar(0, 0, width, height) {}

UICircularBar::UICircularBar(float positionX, float positionY, float width, float height)
        : text("", 0, positionX, positionY, width, height, UITextMode::CENTERED) {
    type = UIComponentType::UICIRCULARBAR;
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
}

void UICircularBar::setBackgroundColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor) {
    this->bgColor.standard = standardColor;
    this->bgColor.hover = hoverColor;
    this->bgColor.pressed = pressedColor;
    if (mode == 0)
        mode = 1;
    else if (mode == 2)
        mode = 3;
    mesh.loadPosition(positionX, positionY, width, height, mode);
}

void UICircularBar::setBackgroundTexture(Texture *texture) {
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
}

void UICircularBar::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
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
}

void UICircularBar::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
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
}

void UICircularBar::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX, positionY);
    mesh.loadPosition(positionX, positionY, width, height);
}

void UICircularBar::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.loadPosition(positionX, positionY, width, height);
}

void UICircularBar::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x, y, w, h);
    mesh.loadPosition(positionX, positionY, width, height);
}

void UICircularBar::setText(char *string, Font *font, int fontSize) {
    text.text = string;
    text.font = font;
    text.positionX = positionX;
    text.positionY = positionY;
    text.setFontSize(fontSize);
}

void UICircularBar::setText(char *string) {
    text.setText(string);
}

void UICircularBar::setFont(Font *font) {
    text.setFont(font);
}

void UICircularBar::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
}

void UICircularBar::setTextColor(const UIColor& color) {
    this->fgColor = color;
}

void UICircularBar::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    mesh.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
}

void UICircularBar::mousePositionInput(double x, double y) {
    bool previous = hovered;
    hovered = COMPONENT_HOVERED(x, y);
    if (previous && !hovered || !previous && hovered)
        if (callback != nullptr)
            (*callback)(pressed, hovered);
}

void UICircularBar::mouseButtonInput(int action) {
    bool previous = pressed;
    if (action == INPUT_PRESSED) {
        if (hovered)
            pressed = true;
    } else if (action == INPUT_RELEASED)
        pressed = false;
    if (callback != nullptr)
        if (previous && !pressed || !previous && pressed)
            (*callback)(pressed, hovered);
}