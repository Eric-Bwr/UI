#include "QuadMesh.h"

QuadMesh::QuadMesh() {
    vbo.init(nullptr, 0, GL_DYNAMIC_DRAW);
    vao.addBuffer(vbo, DataManager::quadLayout);
}

void QuadMesh::load(float positionX, float positionY, float width, float height, float info){
    vertices.emplace_back(positionX);
    vertices.emplace_back(positionY + height);
    vertices.emplace_back(0);
    vertices.emplace_back(1);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX);
    vertices.emplace_back(positionY);
    vertices.emplace_back(0);
    vertices.emplace_back(0);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX + width);
    vertices.emplace_back(positionY);
    vertices.emplace_back(1);
    vertices.emplace_back(0);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX);
    vertices.emplace_back(positionY + height);
    vertices.emplace_back(0);
    vertices.emplace_back(1);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX + width);
    vertices.emplace_back(positionY);
    vertices.emplace_back(1);
    vertices.emplace_back(0);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX + width);
    vertices.emplace_back(positionY + height);
    vertices.emplace_back(1);
    vertices.emplace_back(1);
    vertices.emplace_back(info);

    vertexCount = vertices.size() / 5;
    vao.bind();
    vbo.subData(vertices.data(), vertexCount * DataManager::quadLayout.getStride(), 0, GL_DYNAMIC_DRAW);
}

void QuadMesh::render(){
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

QuadMesh::~QuadMesh() {
    vertices.clear();
}