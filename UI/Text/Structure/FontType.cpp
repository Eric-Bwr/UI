#include <freetype/ftglyph.h>

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
	    FT_GlyphSlot gs = font->face->glyph;
	    unsigned int glyphIndex = FT_Get_Char_Index(font->face, ascii);
	    FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_RENDER);
	    FT_Render_Glyph(gs, FT_RENDER_MODE_NORMAL);

	    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, ascii - FONT_CHAR_START, gs->bitmap.width, gs->bitmap.rows, 1, GL_RED, GL_UNSIGNED_BYTE, gs->bitmap.buffer);
	    Character ch{};
	    ch.ascii = ascii;
	    ch.width = gs->metrics.width >> 6;
	    ch.height = gs->metrics.height >> 6;
	    ch.advance = gs->metrics.horiAdvance >> 6;
	    ch.bearingX = gs->metrics.horiBearingX >> 6;
	    ch.bearingY = gs->metrics.horiBearingY >> 6;
	    characters.insert(std::make_pair(ascii, ch));


    }
    texture->generateMipMap();
}

FontType::~FontType() {
    delete texture;
}
