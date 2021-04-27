#include "UIText.h"
#include "Font.h"

UIText::UIText(const char *text, int fontSize, float positionX, float positionY, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = TextManager::defaultFont;
    this->fontSize = fontSize;
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY;
    this->width = width;
    this->height = height;
    this->mode = mode;
    this->maxLines = INT_MAX;
    TextManager::loadText(this);
}

UIText::UIText(const char *text, Font* font, int fontSize, float positionX, float positionY, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = font;
    this->fontSize = fontSize;
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY;
    this->width = width;
    this->height = height;
    this->mode = mode;
    this->maxLines = INT_MAX;
    TextManager::loadText(this);
}

void UIText::setMaxLines(int maxLines) {
    this->maxLines = maxLines;
    TextManager::loadText(this);
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
