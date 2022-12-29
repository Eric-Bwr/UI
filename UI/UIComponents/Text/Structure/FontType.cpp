#include "FontType.h"

FontType::FontType(Font *font, int fontSize) : fontSize(fontSize) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    texture.init(GL_TEXTURE_2D_ARRAY);
    texture.bind();
    texture.setWidth(fontSize);
    texture.setHeight(fontSize);
    texture.repeat();
    texture.linear();
    texture.setFormat(GL_RED);
    texture.setInternalFormat(GL_R32F);
    texture.setData(nullptr);
    texture.setDepth(FONT_CHAR_END - FONT_CHAR_START + 3);
    texture.load();
    this->font = font;
    FT_Set_Pixel_Sizes(font->face, 0, fontSize);
    pixelMapped = 1.0f / float(fontSize);
    for (int ascii = FONT_CHAR_START; ascii < FONT_CHAR_END; ascii++)
        loadGlyph(ascii);
    if (!characters.count(' '))
        loadGlyph(' ');
    if (!characters.count('\t'))
        loadGlyph('\t');
    if (!characters.count(PASSWORD_CHARACTER))
        loadGlyph(PASSWORD_CHARACTER);
}

void FontType::loadGlyph(int ascii) {
    FT_GlyphSlot gs = font->face->glyph;
    unsigned int glyphIndex = FT_Get_Char_Index(font->face, ascii);
    FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_FORCE_AUTOHINT);
    FT_Render_Glyph(gs, FT_RENDER_MODE_NORMAL);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, ascii - FONT_CHAR_START, gs->bitmap.width, gs->bitmap.rows, 1, GL_RED, GL_UNSIGNED_BYTE, gs->bitmap.buffer);
    Character ch{};
    ch.ascii = float(ascii);
    ch.width = float(gs->metrics.width >> 6);
    ch.height = float(gs->metrics.height >> 6);
    ch.advance = float(gs->metrics.horiAdvance >> 6);
    ch.bearingX = float(gs->metrics.horiBearingX >> 6);
    ch.bearingY = float(gs->metrics.horiBearingY >> 6);
    ch.textureX = pixelMapped * ch.width;
    ch.textureY = pixelMapped * ch.height;
    characters.insert(std::make_pair(ascii, ch));
    if(ch.height > height)
        height = ch.height;
    if(ch.bearingY > bearing)
        bearing = ch.bearingY;
}

float FontType::getTextWidth(const char *text) {
    float result = 0.0f;
    for (int i = 0; i < strlen(text); i++) {
        if(characters.count(text[i]))
            result += characters.at(text[i]).advance;
    }
    return result;
}

float FontType::getCharacterWidth(int ascii) {
    if(characters.count(ascii))
        return characters.at(ascii).advance;
    else
        return 0.0f;
}

float FontType::getHeight() {
    return height;
}

float FontType::getOffset() {
    return height - bearing;
}

FontType::~FontType() {
    characters.clear();
}