#include "UIText.h"
#include "../Text/Font.h"

UIText::UIText(const char *text, int fontSize, float positionX, float positionY) : text(text), font(TextManager::defaultFont), fontSize(fontSize), positionX(positionX), positionY(positionY) {
    TextManager::loadText(this);
}

UIText::UIText(const char *text, Font* font, int fontSize, float positionX, float positionY) : text(text), font(font), fontSize(fontSize), positionX(positionX), positionY(positionY) {
    TextManager::loadText(this);
}
