#include "TextMesh.h"
#include "FontType.h"
#include "../../Components/UIText.h"

TextMesh::TextMesh() {
    vao = new VertexArrayObject();
    vbo = new VertexBufferObject(nullptr, 0, GL_DYNAMIC_DRAW);
    vao->addBuffer(*vbo, TextManager::bufferObjectLayout);
}

void TextMesh::loadText(UIText *uiText, FontType* fontType) {
	texture = fontType->texture;
    vertices.clear();

    float cursorX = uiText->positionX;
    float cursorY = uiText->positionY;
    auto length = strlen(uiText->text);
    auto text = uiText->text;
    int currentLine = 0;
    for (int i = 0; i < length; ++i) {
    	Character c = fontType->characters[text[i]];

        float nextSpaceLength = 0.0f;
        for(int j = i; j < length; j++){
            if(text[j] == ' '){
                break;
            }
            nextSpaceLength += fontType->characters[text[j]].advance;
        }
        if(cursorX + c.advance + nextSpaceLength > uiText->width || text[i] == '\n'){
            cursorX = uiText->positionX;
            currentLine++;
            if(cursorY + fontType->fontSize > uiText->height ||currentLine >= uiText->maxLines)
                break;
            cursorY += fontType->fontSize;
        }

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
