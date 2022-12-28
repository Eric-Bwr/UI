#include "Font.h"
#include "Logger/Logger.h"

void Font::init(const char* path, int faceIndex) {
    this->path = path;
    errorCode = FT_New_Face(DataManager::library, path, faceIndex, &face);
    if(errorCode != 0) {
        logError("Failed to load Font: ", path);
        logWarn("Default font paths may differ from system to system");
    }
}

Font::~Font() {
    FT_Done_Face(face);
}