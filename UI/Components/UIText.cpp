#include "UIText.h"
#include "../Text/Font.h"

UIText::UIText(const char *text, int fontSize) : text(text), font(TextManager::defaultFont), fontSize(fontSize){
    TextManager::loadText(font, this);
}

UIText::UIText(const char *text, Font* font, int fontSize) : text(text), font(font), fontSize(fontSize) {
    TextManager::loadText(font, this);
}
