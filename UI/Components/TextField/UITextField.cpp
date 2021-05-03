#include "UITextField.h"
#include "../Text/Structure/FontType.h"

UITextField::UITextField(const char* defaultText, float width, float height)
        : text(defaultText, height, positionX, positionY, width, height, UITextMode::CENTERED_VERTICAL_LEFT) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->defaultText = defaultText;
    this->content = defaultText;
    this->positionX = 0;
    this->positionY = 0;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_WHITE;
    this->fgColor = COLOR_RED;
    this->cursorColor = COLOR_BLACK;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    this->cursorX = positionX;
    this->fontType = DataManager::getFontType(&text);
    mesh.load(positionX, positionY, width, height, 0);
    cursorMesh.load(cursorX, positionY, cursorWidth, height, 0);
}

UITextField::UITextField(const char* defaultText, float positionX, float positionY, float width, float height)
        : text(defaultText, 110, positionX, positionY, width, height, UITextMode::CENTERED_VERTICAL_LEFT) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->defaultText = defaultText;
    this->content = defaultText;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_WHITE;
    this->fgColor = COLOR_RED;
    this->cursorColor = COLOR_BLACK;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    this->cursorX = positionX;
    this->fontType = DataManager::getFontType(&text);
    mesh.load(positionX, positionY, width, height, 0);
    cursorMesh.load(cursorX, positionY, cursorWidth, height, 0);
}

void UITextField::setTexture(Texture *texture) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UITextField::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX, positionY);
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    cursorMesh.load(cursorX, positionY, cursorWidth, height, 0);
}

void UITextField::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    cursorMesh.load(cursorX, positionY, cursorWidth, height, 0);
}

void UITextField::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x, y, w, h);
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    cursorMesh.load(cursorX, positionY, cursorWidth, height, 0);
}
/*
void UITextField::setText(const char *string, Font *font, int fontSize) {
    text.text = string;
    text.font = font;
    text.positionX = positionX;
    text.positionY = positionY;
    text.setFontSize(fontSize);
}

void UITextField::setText(const char *string) {
    text.setText(string);
}

void UITextField::setFont(Font *font) {
    text.setFont(font);
}

void UITextField::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
}
*/

void UITextField::keyInput(int key, int action, int mods) {
    if(pressed){
        if(key == KEY_BACKSPACE){
        }
    }
}

void UITextField::charInput(unsigned int key) {
    if(pressed){
        if(content == defaultText)
            content.clear();
        content += char(key);
        text.setText(content.c_str());
        cursorX = positionX + fontType->getTextWidth(content.c_str());
        cursorMesh.load(cursorX, positionY, cursorWidth, height, 0);
    }
}

void UITextField::mousePositionInput(double x, double y) {
    hovered = COMPONENT_HOVERED(x, y);
}

void UITextField::mouseButtonInput(int button, int action) {
    if (button == MOUSE_BUTTON_PRESSED && action == INPUT_PRESSED) {
        if (hovered) {
            pressed = true;

        }else
            pressed = false;
    }
}