#include "TextManager.h"
#include "Font.h"
#include "Structure/FontType.h"
#include "../Components/UIText.h"

FT_Library TextManager::library;
Font *TextManager::defaultFont;
static std::map<const char*, std::vector<FontType*>*> fonts;

static bool shouldInit = true;

int TextManager::init() {
    if (shouldInit) {
        shouldInit = false;
        int errorCode = FT_Init_FreeType(&library);
        defaultFont = new Font(DEFAULT_FONT_PATH);
        bufferObjectLayout.pushFloat(2);
        bufferObjectLayout.pushFloat(1);
        return errorCode;
    } else
        return -1;
}

void TextManager::loadText(Font *font, UIText *uiText) {
    std::vector<FontType *>* fontTypeBatch;
    FontType* fontType = nullptr;
    if (!fonts.count(font->path)) {
        fontTypeBatch = new std::vector<FontType *>;
        fonts.insert(std::pair<const char*, std::vector<FontType *>*>(font->path, fontTypeBatch));
        fontType = new FontType(font, uiText->fontSize);
        fontTypeBatch->emplace_back(fontType);
    } else {
        fontTypeBatch = fonts.find(font->path)->second;
        for(auto type : *fontTypeBatch){
            if(type->fontSize == uiText->fontSize){
                fontType = type;
                break;
            }
        }
        if(fontType == nullptr) {
            fontType = new FontType(font, uiText->fontSize);
            fontTypeBatch->emplace_back(fontType);
        }
    }
    uiText->textMesh.loadText(uiText, fontType);
}

TextManager::~TextManager() {
    FT_Done_FreeType(library);
}
