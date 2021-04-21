#include "Font.h"

bool Font::init(const char* path, int faceIndex) {
    return !FT_New_Face(TextManager::library, path, faceIndex, &face);
}

bool Font::setSize(unsigned int width, unsigned int height) {
    return !FT_Set_Pixel_Sizes(face, width, height);
}

Font::~Font() {
    FT_Done_Face(face);
}