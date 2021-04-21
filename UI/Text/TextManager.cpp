#include "TextManager.h"

FT_Library TextManager::library;
bool shouldInit = true;

int TextManager::init() {
    if(shouldInit) {
        shouldInit = false;
        return FT_Init_FreeType(&library);
    } else
        return -1;
}
