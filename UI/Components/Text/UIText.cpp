#include "UIText.h"
#include "Font.h"

UIText::UIText(const char *text, int fontSize, float positionX, float positionY, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = TextManager::defaultFont;
    this->fontSize = fontSize;
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY + fontSize;
    this->width = width;
    this->height = height;
    this->mode = mode;
    TextManager::loadText(this);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

UIText::UIText(const char *text, Font* font, int fontSize, float positionX, float positionY, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = font;
    this->fontSize = fontSize;
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY + fontSize;
    this->width = width;
    this->height = height;
    this->mode = mode;
    TextManager::loadText(this);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

void UIText::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY;
    TextManager::loadText(this);
}

void UIText::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    TextManager::loadText(this);
}

void UIText::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    TextManager::loadText(this);
}

void UIText::setMode(int mode) {
    this->mode = mode;
    TextManager::loadText(this);
}