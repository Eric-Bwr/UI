#include "DataManager.h"
#include "UI/UIComponents/Text/Font.h"
#include "UI/UIComponents/Text/Structure/FontType.h"
#include "UI/UIComponents/Text/UIText.h"

FT_Library DataManager::library;
Font *DataManager::defaultFont;
VertexBufferObjectLayout DataManager::textLayout;
VertexBufferObjectLayout DataManager::quadLayout;
static std::map<const char*, std::vector<FontType*>*> fonts;

static bool shouldInit = true;

int DataManager::init() {
    if (shouldInit) {
        shouldInit = false;
        int errorCode = FT_Init_FreeType(&library);
        defaultFont = new Font();
        defaultFont->init(DEFAULT_FONT_PATH);
        textLayout.pushFloat(2);
        textLayout.pushFloat(2);
        textLayout.pushFloat(1);
        quadLayout.pushFloat(2);
        quadLayout.pushFloat(2);
        quadLayout.pushFloat(1);
        quadLayout.pushFloat(4);
        return errorCode;
    } else
        return -1;
}

FontType* DataManager::getFontType(UIText *uiText) {
    return getFontType(uiText->font, uiText->fontSize);
}

FontType *DataManager::getFontType(Font *font, int fontSize) {
    std::vector<FontType *>* fontTypeBatch;
    FontType* fontType = nullptr;
    if (!fonts.count(font->path)) {
        fontTypeBatch = new std::vector<FontType *>;
        fonts.insert(std::pair<const char*, std::vector<FontType *>*>(font->path, fontTypeBatch));
        fontType = new FontType(font, fontSize);
        fontTypeBatch->emplace_back(fontType);
    } else {
        fontTypeBatch = fonts.find(font->path)->second;
        for(auto type : *fontTypeBatch){
            if(type->fontSize == fontSize){
                fontType = type;
                break;
            }
        }
        if(fontType == nullptr) {
            fontType = new FontType(font, fontSize);
            fontTypeBatch->emplace_back(fontType);
        }
    }
    return fontType;
}

DataManager::~DataManager() {
    FT_Done_FreeType(library);
    delete defaultFont;
    for (auto elementPair : fonts) {
        for (auto element : *elementPair.second)
            delete element;
        delete elementPair.second;
    }
}