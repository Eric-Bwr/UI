#include "TextManager.h"
#include "Font.h"
#include "../Components/UIText.h"

FT_Library TextManager::library;
Font *TextManager::defaultFont;
bool shouldInit = true;

static int width;
static int height;

int TextManager::init() {
    if (shouldInit) {
        shouldInit = false;
        int errorCode = FT_Init_FreeType(&library);
        defaultFont = new Font(DEFAULT_FONT_PATH);
        return errorCode;
    } else
        return -1;
}

void TextManager::loadText(const char *text, Font *font, int fontSize, UIText *uiText) {

}

TextManager::~TextManager() {
    FT_Done_FreeType(library);
}
