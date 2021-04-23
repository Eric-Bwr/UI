#include "TextMesh.h"
#include "FontType.h"
#include "../../Components/UIText.h"

TextMesh::TextMesh() {
    vao = new VertexArrayObject();
    vbo = new VertexBufferObject(nullptr, 0, GL_DYNAMIC_DRAW);
    vao->addBuffer(*vbo, TextManager::bufferObjectLayout);
}

void TextMesh::loadText(UIText *uiText, FontType* fontType) {
    vertices.clear();
    //FORMAT:   X Y
    //          LEVEL (ASCII CODE)
    for(int i = 0; i < strlen(uiText->text); i++){
        //PER VERTEX
       // vertices.emplace_back(vertexX);
       // vertices.emplace_back(vertexY);
        vertices.emplace_back(fontType->characters.at(uiText->text[i]).ascii);
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
