#pragma once

#include <map>
#include <cstdint>
#include <cstdio>
#include <Texture.h>
#include "TrueType.h"

#define FONT_SIZE 32
#define FONT_OVERSAMPLING_VERTICAL 2
#define FONT_OVERSAMPLING_HORIZONTAL 2
#define FONT_CHAR_START 32
#define FONT_CHAR_END 96

struct FontError{
    bool failedToInitFont = false;
    bool fileDoesNotExit = false;
    bool fileHasErrors = false;
};

class Font {
public:
    Font(const char* fontPath, float fontSize);
    inline stbtt_fontinfo getFontInfo() { return fontInfo; }
    inline stbtt_packedchar* getCharData() { return charData; }
    inline float getFontSize() { return fontSize; }
    inline float getHighestCharacter() { return highestCharacter; }
    inline float getScale() { return scale; }
    bool hasErrors() const;
    std::string getErrorMessage();
    inline FontError& getFontError() { return fontError; }
    ~Font();
private:
    const char* fontPath;
    FontError fontError;
    float fontSize = 0, highestCharacter = 0, scale = 0;
    int ascent, descent, lineGap, baseline;
    stbtt_fontinfo fontInfo;
    stbtt_packedchar charData[FONT_CHAR_END - FONT_CHAR_START];
    Texture* texture;
};