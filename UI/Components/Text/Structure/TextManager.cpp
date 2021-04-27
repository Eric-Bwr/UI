#include "TextManager.h"
#include "Components/Text/Font.h"
#include "Components/Text/Structure/FontType.h"
#include "Components/Text/UIText.h"

FT_Library TextManager::library;
Font *TextManager::defaultFont;
VertexBufferObjectLayout TextManager::bufferObjectLayout;
int TextManager::windowWidth, TextManager::windowHeight;
static std::map<const char*, std::vector<FontType*>*> fonts;

static bool shouldInit = true;

int TextManager::init() {
    if (shouldInit) {
        shouldInit = false;
        int errorCode = FT_Init_FreeType(&library);
        defaultFont = new Font(DEFAULT_FONT_PATH);
        bufferObjectLayout.pushFloat(2);
        bufferObjectLayout.pushFloat(2);
        bufferObjectLayout.pushFloat(1);
        return errorCode;
    } else
        return -1;
}

void TextManager::loadText(UIText *uiText) {
    std::vector<FontType *>* fontTypeBatch;
    FontType* fontType = nullptr;
    if (!fonts.count(uiText->font->path)) {
        fontTypeBatch = new std::vector<FontType *>;
        fonts.insert(std::pair<const char*, std::vector<FontType *>*>(uiText->font->path, fontTypeBatch));
        fontType = new FontType(uiText->font, uiText->fontSize);
        fontTypeBatch->emplace_back(fontType);
    } else {
        fontTypeBatch = fonts.find(uiText->font->path)->second;
        for(auto type : *fontTypeBatch){
            if(type->fontSize == uiText->fontSize){
                fontType = type;
                break;
            }
        }
        if(fontType == nullptr) {
            fontType = new FontType(uiText->font, uiText->fontSize);
            fontTypeBatch->emplace_back(fontType);
        }
    }
    uiText->textMesh.loadText(uiText, fontType);
}

void TextManager::setSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

TextManager::~TextManager() {
    FT_Done_FreeType(library);
    delete defaultFont;
    for (auto elementPair : fonts) {
        for (auto element : *elementPair.second)
            delete element;
        delete elementPair.second;
    }
}