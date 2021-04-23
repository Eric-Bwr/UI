#include "FontType.h"

FontType::FontType(Font *font, int fontSize) : fontSize(fontSize){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    texture = new Texture(GL_TEXTURE_2D_ARRAY);
    texture->bind();
    texture->setWidth(fontSize);
    texture->setHeight(fontSize);
    texture->clampEdge();
    texture->setFormat(GL_RED);
    texture->setInternalFormat(GL_R8);
    texture->setData(nullptr);
    texture->setDepth(FONT_CHAR_END - FONT_CHAR_START);
    texture->load();
    FT_Set_Pixel_Sizes(font->face, 0, fontSize);
    for (int ascii = FONT_CHAR_START; ascii < FONT_CHAR_END; ascii++) {
    	FT_GlyphSlot glyph = font->face->glyph;
        unsigned int glyphIndex = FT_Get_Char_Index(font->face, ascii);
        //HANDLE ERROR                          HANDLE \/
        FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_RENDER);
        //HANDLE ERROR                          HANDLE \/
        FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, ascii - FONT_CHAR_START, glyph->bitmap.width, glyph->bitmap.rows, 1, GL_RED, GL_UNSIGNED_BYTE, font->slot->bitmap.buffer);
        Character ch;
        ch.ascii = ascii;
        ch.width = glyph->bitmap.width;
        ch.height = glyph->bitmap.rows;
        ch.advance = glyph->advance.x;
        ch.bearingX = glyph->bitmap_left;
        ch.bearingY = glyph->bitmap_top;
        characters.insert(std::pair<int, Character>(ascii, ch));
    }
}

FontType::~FontType() {
    delete texture;
}
