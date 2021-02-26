#include "Font.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

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
    }
	scale = stbtt_ScaleForPixelHeight(&fontInfo, fontSize);
    stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);
    baseline = (int)((float)ascent * scale);

    int bw = FONT_SIZE * AMOUNT_CHARS;

    auto* bitmap = (uint8_t*)calloc(bw * FONT_SIZE, sizeof(uint8_t));
    int x = 0;
    for (int i = FONT_CHAR_START; i < FONT_CHAR_END; i++){
        int aW;
        int lsb;
        stbtt_GetCodepointHMetrics(&fontInfo, i, &aW, &lsb);
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&fontInfo, i, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
        int y = ascent + c_y1;
        int byteOffset = x + roundf(lsb * scale) + (y * bw);
        stbtt_MakeCodepointBitmap(&fontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, bw, scale, scale, i);
        x += roundf(aW * scale);
        int kern = stbtt_GetCodepointKernAdvance(&fontInfo, i, i + 1);
        x += roundf(kern * scale);
    }


    texture = new Texture(GL_TEXTURE_2D);
    texture->bind();
    texture->setWidth(FONT_SIZE * AMOUNT_CHARS);
    texture->setHeight(FONT_SIZE);
    texture->setData(bitmap);
    texture->setFormat(GL_ALPHA);
    texture->setInternalFormat(GL_ALPHA);
    texture->load(true);
    texture->minLinear();
    texture->magLinear();
    texture->generateMipMap();

	//printf("Write file!\n");
	//stbi_write_png("jadsijadiwjdia.png", bw, FONT_SIZE, 1, bitmap, bw);
	//printf("Written file!\n");

	//free(fontBuffer);
	//free(bitmap);
}

/*
    float width = 0;
	for(int i = 0; text[i]; i++) {
		if (text[i] >= 32 && text[i] < 128) {
			stbtt_packedchar* info = &font->chars[text[i] - 32];
			width += info->xadvance;
		}
	}
	return width;
 */

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
}