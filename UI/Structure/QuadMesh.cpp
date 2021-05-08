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

    vbo.subData(vertices.data(), 6 * DataManager::quadLayout.getStride(), 0, GL_DYNAMIC_DRAW);
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

    vbo.subData(vertices.data(), 6 * DataManager::quadLayout.getStride(), 0, GL_DYNAMIC_DRAW);
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

    vbo.subData(vertices.data(), 6 * DataManager::quadLayout.getStride(), 0, GL_DYNAMIC_DRAW);
}

void QuadMesh::render() {
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

QuadMesh::~QuadMesh() {
    vertices.clear();
}

void QuadMeshTriplet::loadPosition(float x, float y, float w, float h,
                                   float xx, float yy, float ww, float hh,
                                   float xxx, float yyy, float www, float hhh) {
    meshes[0].loadPosition(x, y, w, h);
    meshes[1].loadPosition(xx, yy, ww, hh);
    meshes[2].loadPosition(xxx, yyy, www, hhh);
}

void QuadMeshTriplet::loadPosition(float x, float y, float w, float h) {
    meshes[0].loadPosition(x, y, w, h);
    meshes[1].loadPosition(x, y, w, h);
    meshes[2].loadPosition(x, y, w, h);
}

void QuadMeshTriplet::load(float x, float y, float w, float h,
                           float xx, float yy, float ww, float hh,
                           float xxx, float yyy, float www, float hhh, float info) {
    meshes[0].load(x, y, w, h, info);
    meshes[1].load(xx, yy, ww, hh, info);
    meshes[2].load(xxx, yyy, www, hhh, info);
}

void QuadMeshTriplet::load(float x, float y, float w, float h, float info) {
    meshes[0].load(x, y, w, h, info);
    meshes[1].load(x, y, w, h, info);
    meshes[2].load(x, y, w, h, info);
}

void QuadMeshTriplet::load(float x, float y, float w, float h,
                           float xx, float yy, float ww, float hh,
                           float xxx, float yyy, float www, float hhh,
                           float info, float textureWidth, float textureHeight,
                           float texX, float texY, float texW, float texH,
                           float texXX, float texYY, float texWW, float texHH,
                           float texXXX, float texYYY, float texWWW, float texHHH) {
    meshes[0].load(x, y, w, h, textureWidth, textureHeight, texX, texY, texW, texH, info);
    meshes[1].load(xx, yy, ww, hh, textureWidth, textureHeight, texXX, texYY, texWW, texHH, info);
    meshes[2].load(xxx, yyy, www, hhh, textureWidth, textureHeight, texXXX, texYYY, texWWW, texHHH, info);
}

void QuadMeshTriplet::load(float x, float y, float w, float h,
                           float info, float textureWidth, float textureHeight,
                           float texX, float texY, float texW, float texH,
                           float texXX, float texYY, float texWW, float texHH,
                           float texXXX, float texYYY, float texWWW, float texHHH) {
    meshes[0].load(x, y, w, h, textureWidth, textureHeight, texX, texY, texW, texH, info);
    meshes[1].load(x, y, w, h, textureWidth, textureHeight, texXX, texYY, texWW, texHH, info);
    meshes[2].load(x, y, w, h, textureWidth, textureHeight, texXXX, texYYY, texWWW, texHHH, info);
}

void QuadMeshTriplet::render(int index) {
    meshes[index].vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
