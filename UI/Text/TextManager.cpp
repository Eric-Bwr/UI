#include "TextManager.h"
#include "Font.h"
#include "../Components/UIText.h"

FT_Library TextManager::library;
Font *TextManager::defaultFont;
bool shouldInit = true;

static int width;
static int height;

int TextManager::init() {
    if (shouldInit) {
        shouldInit = false;
        int errorCode = FT_Init_FreeType(&library);
        defaultFont = new Font(DEFAULT_FONT_PATH);
        return errorCode;
    } else
        return -1;
}

#include "iostream"
void TextManager::loadText(const char *text, Font *font, unsigned int fontSize, UIText *uiText) {
    FT_Set_Pixel_Sizes(font->face, 0, fontSize);
    int penX = 0;
    int penY = 0;
    height = fontSize;
    for (int i = 0; i < strlen(text); i++) {
        unsigned int glyphIndex = FT_Get_Char_Index(font->face, text[i]);
        //HANDLE ERROR                          HANDLE \/
        FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_NO_BITMAP);
        width += font->slot->advance.x >> 6;
        height += font->slot->advance.y >> 6;
    }
    unsigned char imageBuffer[width][height];
    for (int index = 0; index < strlen(text); index++) {
        unsigned int glyphIndex = FT_Get_Char_Index(font->face, text[index]);
        //HANDLE ERROR                          HANDLE \/
        FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_RENDER);
        //HANDLE ERROR                          HANDLE \/
        FT_Render_Glyph(font->face->glyph, FT_RENDER_MODE_NORMAL);


        int i, j, p, q;
        int x = penX + font->slot->bitmap_left;
        int y = penY - font->slot->bitmap_top;
        int x_max = x + font->slot->bitmap.width;
        int y_max = y + font->slot->bitmap.rows;
        for (j = y, q = 0; j < y_max; j++, q++) {
            for (i = x, p = 0; i < x_max; i++, p++) {
                if (i < 0 || j < 0 || i >= width || j >= height)
                    continue;
                imageBuffer[j][i] |= font->slot->bitmap.buffer[q * font->slot->bitmap.width + p];
            }
        }


        penX += font->slot->advance.x >> 6;
        penY += font->slot->advance.y >> 6;
    }
    std::cout << font->slot->bitmap.width << "\n";
    std::cout << font->slot->bitmap.rows << "\n";
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    uiText->texture.setData(font->slot->bitmap.buffer);
    uiText->texture.clampEdge();
    uiText->texture.setFormat(GL_RED);
    uiText->texture.setInternalFormat(GL_R8);
    uiText->texture.setWidth(font->slot->bitmap.width);
    uiText->texture.setHeight(font->slot->bitmap.rows);
    //MAY CHANGE (SAMPLING)
    uiText->texture.load();
    //glTextureStorage2D(GL_TEXTURE_2D, 1, GL_R8, font->slot->bitmap.width, font->slot->bitmap.rows);
    //glTextureSubImage2D(GL_TEXTURE_2D, 0, 0, 0, font->slot->bitmap.width, font->slot->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, font->slot->bitmap.buffer);
}

TextManager::~TextManager() {
    FT_Done_FreeType(library);
}
