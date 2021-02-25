#include <iostream>
#include "Font.h"

Font::Font(const char *fontPath, float fontSize) : fontPath(fontPath), fontSize(fontSize) {
    FILE *fontFile = fopen(fontPath, "rb");
    if (fontFile == nullptr)
        fontError.fileDoesNotExit = true;
    if (ferror(fontFile))
        fontError.fileHasErrors = true;
    fseek(fontFile, 0, SEEK_END);
    auto size = ftell(fontFile);
    rewind(fontFile);
    auto fontBuffer = (uint8_t *) malloc(size);
    fread(fontBuffer, 1, size, fontFile);
    fclose(fontFile);
    if(!stbtt_InitFont(&fontInfo, fontBuffer, 0)) {
        fontError.failedToInitFont = true;
        free(fontBuffer);
        free(&fontInfo);
    }
    /*
    uint8_t* bitmap;
    int textureSize = FONT_SIZE;
    while(true){
        bitmap = (uint8_t*)malloc(FONT_SIZE * FONT_SIZE);
        stbtt_pack_context packContext;
        stbtt_PackBegin(&packContext, bitmap, FONT_SIZE, FONT_SIZE, 0, 1, nullptr);
        stbtt_PackSetOversampling(&packContext, FONT_OVERSAMPLING_HORIZONTAL, FONT_OVERSAMPLING_VERTICAL);
        if(!stbtt_PackFontRange(&packContext, fontBuffer, 0, size, FONT_CHAR_START, FONT_CHAR_END, charData)){
            free(bitmap);
            stbtt_PackEnd(&packContext);
            textureSize *= 2;
        }else {
            stbtt_PackEnd(&packContext);
            break;
        }
    }
    */
/*

    texture = new Texture(GL_TEXTURE_2D);
    texture->setWidth(FONT_WIDTH);
    texture->setHeight(FONT_HEIGHT);
    texture->setData(tmpBitmap);
    texture->setFormat(GL_ALPHA);
    texture->setInternalFormat(GL_ALPHA);
    texture->load();
    texture->minLinear();
    texture->magLinear();
    texture->generateMipMap();
    highestCharacter = charData['H' - FONT_CHAR_START].y1 - charData['H' - FONT_CHAR_START].y0;
    spaceWidth = charData[' ' - FONT_CHAR_START].xadvance;
    for (int i = FONT_CHAR_START; i < FONT_CHAR_END; i++) {
        stbtt_bakedchar characterData = charData[i - FONT_CHAR_START];
        characters.insert(std::pair<char, Character *>(char(i), new Character(i, characterData.x0, characterData.y0, characterData.x1, characterData.y1, characterData.xoff, characterData.yoff, characterData.xadvance)));
    }
     */
}

bool Font::hasErrors() const {
    return fontError.failedToInitFont || fontError.fileHasErrors || fontError.fileDoesNotExit;
}

std::string Font::getErrorMessage() {
    std::string msg = fontPath;
    msg.append("\n");
    if (hasErrors()) {
        if (fontError.failedToInitFont)
            msg.append("Failed to init Font\n");
        if (fontError.fileHasErrors)
            msg.append("File has Errors\n");
        if (fontError.fileDoesNotExit)
            msg.append("Failed to locate File\n");
    } else
        msg.append("Loaded successfully\n");
    return msg;
}

Font::~Font() {
    delete texture;
    free(&fontInfo);
}