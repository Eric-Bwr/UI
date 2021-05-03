#include "TextMesh.h"
#include "FontType.h"
#include "../UIText.h"

TextMesh::TextMesh() {
    vbo.init(nullptr, 0, GL_DYNAMIC_DRAW);
    vao.addBuffer(vbo, DataManager::textLayout);
}

struct Word {
    std::vector<char> characters;
    float width = 0.0f;
    float spaceWidth = 0.0f;
};

struct Line {
    std::vector<Word> words;
    float lineWidth = 0.0f;
};

void TextMesh::loadText(UIText *uiText, FontType *fontType) {
    texture = fontType->texture;
    vertices.clear();
    auto length = strlen(uiText->text);
    auto spaceWidth = fontType->characters[' '].advance;
    auto bearing = fontType->characters['|'].bearingY + 2;
    auto height = fontType->characters['|'].height;
    auto cutoff = height - (bearing - 2);
    Word currentWord;
    std::vector<Word> words;
    for (int i = 0; i < length; i++) {
        char currentChar = uiText->text[i];
        if (currentChar == ' ') {
            if (!currentWord.characters.empty())
                words.emplace_back(currentWord);
            currentWord.characters.clear();
            currentWord.width = 0.0f;
            currentWord.spaceWidth = spaceWidth;
            words.emplace_back(currentWord);
            currentWord.width = 0.0f;
            currentWord.spaceWidth = 0.0f;
        } else if (currentChar == '\n') {
            currentWord.characters.emplace_back(currentChar);
            words.emplace_back(currentWord);
            currentWord.width = 0.0f;
            currentWord.spaceWidth = 0.0f;
            currentWord.characters.clear();
        } else {
            currentWord.width += fontType->characters[currentChar].advance;
            currentWord.characters.emplace_back(currentChar);
            if (i == length - 1)
                words.emplace_back(currentWord);
        }
    }
    Line currentLine;
    std::vector<Line> lines;
    for (auto &word : words) {
        if (word.characters.empty()) {
            currentLine.lineWidth += word.width + word.spaceWidth;
            currentLine.words.emplace_back(word);
        } else {
            if (word.characters.back() == '\n') {
                word.characters.pop_back();
                if (currentLine.lineWidth + word.width + word.spaceWidth <= uiText->width) {
                    currentLine.words.emplace_back(word);
                    currentLine.lineWidth += word.width + word.spaceWidth;
                } else {
                    lines.emplace_back(currentLine);
                    currentLine.words.clear();
                    currentLine.words.emplace_back(word);
                    currentLine.lineWidth = 0.0f;
                    currentLine.lineWidth += word.width + word.spaceWidth;
                }
                lines.emplace_back(currentLine);
                currentLine.words.clear();
                currentLine.lineWidth = 0.0f;
            } else if (currentLine.lineWidth + word.width + word.spaceWidth <= uiText->width) {
                currentLine.words.emplace_back(word);
                currentLine.lineWidth += word.width + word.spaceWidth;
            } else {
                lines.emplace_back(currentLine);
                currentLine.words.clear();
                currentLine.words.emplace_back(word);
                currentLine.lineWidth = 0.0f;
                currentLine.lineWidth += word.width + word.spaceWidth;
            }
        }
    }
    lines.emplace_back(currentLine);
    float cursorX;
    float cursorY;
    if (uiText->mode == UITextMode::CENTERED_VERTICAL_RIGHT || uiText->mode == UITextMode::CENTERED_VERTICAL_LEFT || uiText->mode == UITextMode::CENTERED)
        if (lines.size() * uiText->fontSize >= uiText->height)
            cursorY = uiText->positionY + bearing;
        else
            cursorY = uiText->positionY + ((uiText->height / 2) - ((lines.size() * uiText->fontSize) / 2) + height - cutoff / 2);
    else
        cursorY = uiText->positionY + bearing;
    for (const auto &line : lines) {
        if (!line.words.empty() && line.words.at(0).width > uiText->width)
            break;
        if (uiText->mode == UITextMode::CENTERED_HORIZONTAL || uiText->mode == UITextMode::CENTERED)
            if (line.words.empty() || line.words.back().characters.empty())
                cursorX = uiText->positionX + ((uiText->width / 2) - (line.lineWidth / 2)) + spaceWidth;
            else
                cursorX = uiText->positionX + ((uiText->width / 2) - (line.lineWidth / 2));
        else if (uiText->mode == UITextMode::RIGHT || uiText->mode == UITextMode::CENTERED_VERTICAL_RIGHT)
            if (line.words.empty() || line.words.back().characters.empty())
                cursorX = uiText->positionX + uiText->width - line.lineWidth + spaceWidth;
            else
                cursorX = uiText->positionX + uiText->width - line.lineWidth;
        else
            cursorX = uiText->positionX;
        if (cursorY - uiText->positionY + cutoff > uiText->height)
            break;
        for (const auto &word : line.words) {
            cursorX += word.spaceWidth;
            for (auto character : word.characters) {
                Character c = fontType->characters[character];
                auto x = cursorX + c.bearingX;
                auto y = cursorY - c.bearingY;

                vertices.emplace_back(x);
                vertices.emplace_back(y + c.height);
                vertices.emplace_back(0);
                vertices.emplace_back(c.textureY);
                vertices.emplace_back(c.ascii);

                vertices.emplace_back(x);
                vertices.emplace_back(y);
                vertices.emplace_back(0);
                vertices.emplace_back(0);
                vertices.emplace_back(c.ascii);

                vertices.emplace_back(x + c.width);
                vertices.emplace_back(y);
                vertices.emplace_back(c.textureX);
                vertices.emplace_back(0);
                vertices.emplace_back(c.ascii);

                vertices.emplace_back(x);
                vertices.emplace_back(y + c.height);
                vertices.emplace_back(0);
                vertices.emplace_back(c.textureY);
                vertices.emplace_back(c.ascii);

                vertices.emplace_back(x + c.width);
                vertices.emplace_back(y);
                vertices.emplace_back(c.textureX);
                vertices.emplace_back(0);
                vertices.emplace_back(c.ascii);

                vertices.emplace_back(x + c.width);
                vertices.emplace_back(y + c.height);
                vertices.emplace_back(c.textureX);
                vertices.emplace_back(c.textureY);
                vertices.emplace_back(c.ascii);
                cursorX += c.advance;
            }
        }
        cursorY += fontType->fontSize;
    }
    vertexCount = vertices.size() / 5;
    vao.bind();
    vbo.subData(vertices.data(), vertexCount * DataManager::textLayout.getStride(), 0, GL_DYNAMIC_DRAW);
}

void TextMesh::render() {
    vao.bind();
    texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

TextMesh::~TextMesh() {
    vertices.clear();
}
