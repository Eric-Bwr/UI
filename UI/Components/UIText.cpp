#include "UIText.h"
#include "../Text/Font.h"

UIText::UIText(const char *text, unsigned int fontSize) : text(text), font(TextManager::defaultFont), fontSize(fontSize){
    TextManager::loadText(text, font, fontSize, this);
}

UIText::UIText(const char *text, Font* font, unsigned int fontSize) : text(text), font(font), fontSize(fontSize) {
    TextManager::loadText(text, font, fontSize, this);
}
