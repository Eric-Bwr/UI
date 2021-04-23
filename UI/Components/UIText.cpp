#include "UIText.h"
#include "../Text/Font.h"

UIText::UIText(const char *text, int fontSize) : text(text), font(TextManager::defaultFont), fontSize(fontSize){
    TextManager::loadText(text, font, fontSize, this);
    textMesh.init();
}

UIText::UIText(const char *text, Font* font, int fontSize) : text(text), font(font), fontSize(fontSize) {
    TextManager::loadText(text, font, fontSize, this);
    textMesh.init();
}
