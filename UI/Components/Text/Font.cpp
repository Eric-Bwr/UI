#include "Font.h"

Font::Font(const char* path, int faceIndex) : path(path) {
    errorCode = FT_New_Face(TextManager::library, path, faceIndex, &face);
    slot = face->glyph;
}

Font::~Font() {
    FT_Done_Face(face);
}