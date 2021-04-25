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

	auto characters = fontType->characters;
    auto fontSize = (float) fontType->fontSize;
	auto text = uiText->text;
    auto wwidth = (float)TextManager::windowWidth;
    auto wheight = (float)TextManager::windowHeight;

    int xoff = 200; /* x, y start positions */
    int yoff = 300;
    for (int i = 0; i < strlen(text); ++i) {
    	Character c = characters[text[i]];

    	auto ascii = (float)c.ascii;
    	auto x = (float)(xoff + c.bearingX);
    	auto y = yoff - c.bearingY;
    	auto w = (float)c.width;
    	auto h = (float)c.height;

		vertices.push_back(x);
		vertices.push_back(y + h);
		vertices.push_back(0);
		vertices.push_back(1);
		vertices.push_back(ascii);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(ascii);

		vertices.push_back(x + w);
		vertices.push_back(y);
		vertices.push_back(1);
		vertices.push_back(0);
		vertices.push_back(ascii);

		vertices.push_back(x);
		vertices.push_back(y + h);
		vertices.push_back(0);
		vertices.push_back(1);
		vertices.push_back(ascii);

		vertices.push_back(x + w);
		vertices.push_back(y);
		vertices.push_back(1);
		vertices.push_back(0);
		vertices.push_back(ascii);

		vertices.push_back(x + w);
		vertices.push_back(y + h);
		vertices.push_back(1);
		vertices.push_back(1);
		vertices.push_back(ascii);

		xoff += c.advance;
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
