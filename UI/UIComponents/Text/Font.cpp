#include "Font.h"

void Font::init(const char* path, int faceIndex) {
    this->path = path;
    errorCode = FT_New_Face(DataManager::library, path, faceIndex, &face);
}

Font::~Font() {
    FT_Done_Face(face);
}