#include "Font.h"

bool Font::init(const char* path, int faceIndex) {
    return !FT_New_Face(TextManager::library, path, faceIndex, &face);
}

Font::~Font() {
    FT_Done_Face(face);
}