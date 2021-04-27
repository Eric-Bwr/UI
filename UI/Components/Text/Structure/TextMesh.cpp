#include "TextMesh.h"
#include "FontType.h"
#include "../UIText.h"

TextMesh::TextMesh() {
    vao = new VertexArrayObject();
    vbo = new VertexBufferObject(nullptr, 0, GL_DYNAMIC_DRAW);
    vao->addBuffer(*vbo, TextManager::bufferObjectLayout);
}

struct Word {
    std::vector<char> characters;
    float wordWidth = 0.0f;
    float spaceWidth = 0.0f;
    float startSpaceWidth = 0.0f;
};

struct Line {
    std::vector<Word> words;
    float lineWidth = 0.0f;
};

void TextMesh::loadText(UIText *uiText, FontType *fontType) {
    texture = fontType->texture;
    vertices.clear();
    auto length = strlen(uiText->text);
    auto text = uiText->text;
    auto spaceWidth = fontType->characters[' '].advance;
    Word currentWord;
    std::vector<Word> words;
    for (int i = 0; i < length; i++) {
        char currentChar = text[i];
        if (currentChar == ' ') {
            if (currentWord.characters.empty())
                currentWord.startSpaceWidth += spaceWidth;
            else {
                currentWord.spaceWidth += spaceWidth;
                words.emplace_back(currentWord);
                currentWord.spaceWidth = 0.0f;
                currentWord.wordWidth = 0.0f;
                currentWord.startSpaceWidth = 0.0f;
                currentWord.characters.clear();
            }
        }else if(currentChar == '\n'){
            currentWord.characters.emplace_back(currentChar);
            words.emplace_back(currentWord);
            currentWord.startSpaceWidth = 0.0f;
            currentWord.spaceWidth = 0.0f;
            currentWord.wordWidth = 0.0f;
            currentWord.characters.clear();
        } else {
            currentWord.wordWidth += fontType->characters[currentChar].advance;
            currentWord.characters.emplace_back(currentChar);
        }
    }
    words.emplace_back(currentWord);
    Line currentLine;
    std::vector<Line> lines;
    for (auto &word : words) {
        if(word.characters.back() == '\n'){
            word.characters.pop_back();
            if (currentLine.lineWidth + word.spaceWidth + word.wordWidth + word.startSpaceWidth <= uiText->width) {
                currentLine.words.emplace_back(word);
                currentLine.lineWidth += word.wordWidth + word.spaceWidth + word.startSpaceWidth;
            }else{
                lines.emplace_back(currentLine);
                currentLine.words.clear();
                currentLine.lineWidth = 0.0f;
                word.spaceWidth = 0.0f;
                word.startSpaceWidth = 0.0f;
                currentLine.words.emplace_back(word);
                currentLine.lineWidth += word.wordWidth + word.startSpaceWidth;
            }
            lines.emplace_back(currentLine);
            currentLine.words.clear();
            currentLine.lineWidth = 0.0f;
        }else if (currentLine.lineWidth + word.spaceWidth + word.wordWidth + word.startSpaceWidth <= uiText->width) {
            currentLine.words.emplace_back(word);
            currentLine.lineWidth += word.wordWidth + word.spaceWidth + word.startSpaceWidth;
        } else {
            lines.emplace_back(currentLine);
            currentLine.words.clear();
            currentLine.lineWidth = 0.0f;
            currentLine.words.emplace_back(word);
            currentLine.lineWidth += word.wordWidth + word.spaceWidth + word.startSpaceWidth;
        }
    }
    lines.emplace_back(currentLine);

    float cursorX = uiText->positionX;
    float cursorY = uiText->positionY;
    for (const auto &line : lines) {
        for (const auto &word : line.words) {
            cursorX += word.startSpaceWidth;
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
            cursorX += word.spaceWidth;
        }
        cursorY += fontType->fontSize;
        cursorX = uiText->positionX;
    }

    vertexCount = vertices.size() / 5;
    vao->bind();
    vbo->subData(vertices.data(), vertexCount * TextManager::bufferObjectLayout.getStride(), 0, GL_DYNAMIC_DRAW);
}

void TextMesh::render() {
    vao->bind();
    texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

TextMesh::~TextMesh() {
    vertices.clear();
    delete vao;
    delete vbo;
}