#include "FontType.h"

FontType::FontType(Font *font, int fontSize) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    texture = new Texture(GL_TEXTURE_2D_ARRAY);
    texture->bind();
    //THE WIDTH AND HEIGHT IS 0 CAUSE NOTHING IS LOADED,
    //THE MAX WIDTH AND HEIGHT IS NEEDED
    texture->setWidth(font->slot->bitmap.width);
    texture->setHeight(font->slot->bitmap.rows);
    texture->clampEdge();
    texture->setFormat(GL_RED);
    texture->setInternalFormat(GL_R8);
    texture->setData(nullptr);
    texture->setDepth(FONT_CHAR_END - FONT_CHAR_START);
    texture->load();
    FT_Set_Pixel_Sizes(font->face, 0, fontSize);
    for (int ascii = FONT_CHAR_START; ascii < FONT_CHAR_END; ascii++) {
        unsigned int glyphIndex = FT_Get_Char_Index(font->face, ascii);
        //HANDLE ERROR                          HANDLE \/
        FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_RENDER);
        //HANDLE ERROR                          HANDLE \/
        FT_Render_Glyph(font->face->glyph, FT_RENDER_MODE_NORMAL);

        //MAYBE NOT EVEN NEEDED?  unsigned char imageBuffer[width][height];
        //MAYBE NOT EVEN NEEDED?  int i, j, p, q;
        //MAYBE NOT EVEN NEEDED?  int x = penX + font->slot->bitmap_left;
        //MAYBE NOT EVEN NEEDED?  int y = penY - font->slot->bitmap_top;
        //MAYBE NOT EVEN NEEDED?  int x_max = x + font->slot->bitmap.width;
        //MAYBE NOT EVEN NEEDED?  int y_max = y + font->slot->bitmap.rows;
        //MAYBE NOT EVEN NEEDED?  for (j = y, q = 0; j < y_max; j++, q++) {
        //MAYBE NOT EVEN NEEDED?      for (i = x, p = 0; i < x_max; i++, p++) {
        //MAYBE NOT EVEN NEEDED?          if (i < 0 || j < 0 || i >= width || j >= height)
        //MAYBE NOT EVEN NEEDED?              continue;
        //MAYBE NOT EVEN NEEDED?          imageBuffer[j][i] |= font->slot->bitmap.buffer[q * font->slot->bitmap.width + p];
        //MAYBE NOT EVEN NEEDED?      }
        //MAYBE NOT EVEN NEEDED?  }

        //MAY NEED THE IMAGEBUFFER THING FROM ABOVE

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, ascii, font->face->glyph->bitmap.width,
                        font->face->glyph->bitmap.rows, 1, GL_RED, GL_UNSIGNED_BYTE, font->slot->bitmap.buffer);
        Character character;
        character.ascii = ascii;
        characters.insert(std::pair<int, Character>(ascii, character));
    }
}