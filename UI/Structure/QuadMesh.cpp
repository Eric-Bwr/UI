#include "QuadMesh.h"

QuadMesh::QuadMesh() {
    vbo.init(nullptr, 0, GL_DYNAMIC_DRAW);
    vao.addBuffer(vbo, DataManager::quadLayout);
}

void QuadMesh::loadPosition(float positionX, float positionY, float width, float height) {
    vertices.at(0) = positionX;
    vertices.at(1) = positionY + height;

    vertices.at(5) = positionX;
    vertices.at(6) = positionY;

    vertices.at(10) = positionX + width;
    vertices.at(11) = positionY;

    vertices.at(15) = positionX;
    vertices.at(16) = positionY + height;

    vertices.at(20) = positionX + width;
    vertices.at(21) = positionY;

    vertices.at(25) = positionX + width;
    vertices.at(26) = positionY + height;

    vao.bind();
    vbo.subData(vertices.data(), vertexCount * DataManager::quadLayout.getStride(), 0, GL_DYNAMIC_DRAW);
}

void QuadMesh::load(float positionX, float positionY, float width, float height, float info) {
    vertices.clear();

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

void QuadMesh::load(float positionX, float positionY, float width, float height, float textureWidth, float textureHeight, float textureX, float textureY, float textureRegionWidth, float textureRegionHeight, float info) {
    vertices.clear();

    vertices.emplace_back(positionX);
    vertices.emplace_back(positionY + height);
    vertices.emplace_back(textureX / textureWidth);
    vertices.emplace_back((textureY + textureRegionHeight) / textureHeight);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX);
    vertices.emplace_back(positionY);
    vertices.emplace_back(textureX / textureWidth);
    vertices.emplace_back(textureY / textureHeight);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX + width);
    vertices.emplace_back(positionY);
    vertices.emplace_back((textureX + textureRegionWidth) / textureWidth);
    vertices.emplace_back(textureY / textureHeight);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX);
    vertices.emplace_back(positionY + height);
    vertices.emplace_back(textureX / textureWidth);
    vertices.emplace_back((textureY + textureRegionHeight) / textureHeight);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX + width);
    vertices.emplace_back(positionY);
    vertices.emplace_back((textureX + textureRegionWidth) / textureWidth);
    vertices.emplace_back(textureY / textureHeight);
    vertices.emplace_back(info);

    vertices.emplace_back(positionX + width);
    vertices.emplace_back(positionY + height);
    vertices.emplace_back((textureX + textureRegionWidth) / textureWidth);
    vertices.emplace_back((textureY + textureRegionHeight) / textureHeight);
    vertices.emplace_back(info);

    vertexCount = vertices.size() / 5;
    vao.bind();
    vbo.subData(vertices.data(), vertexCount * DataManager::quadLayout.getStride(), 0, GL_DYNAMIC_DRAW);
}

void QuadMesh::render() {
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

QuadMesh::~QuadMesh() {
    vertices.clear();
}