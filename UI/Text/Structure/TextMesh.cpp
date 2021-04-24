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

    int ascii = 65;
    float half = 0.5;

    vertices.push_back(-half);
	vertices.push_back(-half);
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(ascii);

	vertices.push_back(half);
	vertices.push_back(-half);
	vertices.push_back(1);
	vertices.push_back(0);
	vertices.push_back(ascii);

	vertices.push_back(half);
	vertices.push_back(half);
	vertices.push_back(1);
	vertices.push_back(1);
	vertices.push_back(ascii);

	vertices.push_back(-half);
	vertices.push_back(-half);
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(ascii);

	vertices.push_back(half);
	vertices.push_back(half);
	vertices.push_back(1);
	vertices.push_back(1);
	vertices.push_back(ascii);

	vertices.push_back(-half);
	vertices.push_back(half);
	vertices.push_back(0);
	vertices.push_back(1);
	vertices.push_back(ascii);

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
