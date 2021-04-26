#include "UIText.h"
#include "../Text/Font.h"

UIText::UIText(const char *text, int fontSize, float positionX, float positionY, float width, float height) : text(text), font(TextManager::defaultFont), fontSize(fontSize) {
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY;
    this->width = width;
    this->height = height;
    this->maxLines = INT_MAX;
    TextManager::loadText(this);
}

UIText::UIText(const char *text, Font* font, int fontSize, float positionX, float positionY, float width, float height) : text(text), font(font), fontSize(fontSize) {
    this->positionX = positionX;
    this->positionY = TextManager::windowHeight - positionY;
    this->width = width;
    this->height = height;
    this->maxLines = INT_MAX;
    TextManager::loadText(this);
}

void UIText::setMaxLines(int maxLines) {
    this->maxLines = maxLines;
    TextManager::loadText(this);
}
