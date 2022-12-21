#include "QuadMesh.h"

UIColorTriplet &UIColorTriplet::operator=(const UIColor &color) {
    standard = color, hover = color, pressed = color;
    return *this;
}

void QuadMesh::init() {
    vao.init();
    vbo.init(nullptr, 0, GL_STATIC_DRAW);
    vao.addBuffer(vbo, DataManager::quadLayout);
    vertices.resize(36);
}

void QuadMesh::loadPosition(float positionX, float positionY, float width, float height) {
    vertices.at(0) = positionX;
    vertices.at(1) = positionY;
    vertices.at(7) = width;
    vertices.at(8) = height;

    vertices.at(9) = positionX + width;
    vertices.at(10) = positionY;
    vertices.at(16) = width;
    vertices.at(17) = height;

    vertices.at(18) = positionX;
    vertices.at(19) = positionY + height;
    vertices.at(25) = width;
    vertices.at(26) = height;

    vertices.at(27) = positionX + width;
    vertices.at(28) = positionY + height;
    vertices.at(34) = width;
    vertices.at(35) = height;
}

void QuadMesh::loadPosition(float positionX, float positionY, float width, float height, float info) {
    vertices.at(0) = positionX;
    vertices.at(1) = positionY;
    vertices.at(5) = info;
    vertices.at(7) = width;
    vertices.at(8) = height;

    vertices.at(9) = positionX + width;
    vertices.at(10) = positionY;
    vertices.at(14) = info;
    vertices.at(16) = width;
    vertices.at(17) = height;

    vertices.at(18) = positionX;
    vertices.at(19) = positionY + height;
    vertices.at(23) = info;
    vertices.at(25) = width;
    vertices.at(26) = height;

    vertices.at(27) = positionX + width;
    vertices.at(28) = positionY + height;
    vertices.at(32) = info;
    vertices.at(34) = width;
    vertices.at(35) = height;
}

void QuadMesh::load(float positionX, float positionY, float width, float height, float info) {
    vertices.at(0) = positionX;
    vertices.at(1) = positionY;
    vertices.at(2) = 0;
    vertices.at(3) = 0;
    vertices.at(4) = corners;
    vertices.at(5) = info;
    vertices.at(6) = radii;
    vertices.at(7) = width;
    vertices.at(8) = height;

    vertices.at(9) = positionX + width;
    vertices.at(10) = positionY;
    vertices.at(11) = 1;
    vertices.at(12) = 0;
    vertices.at(13) = corners;
    vertices.at(14) = info;
    vertices.at(15) = radii;
    vertices.at(16) = width;
    vertices.at(17) = height;

    vertices.at(18) = positionX;
    vertices.at(19) = positionY + height;
    vertices.at(20) = 0;
    vertices.at(21) = 1;
    vertices.at(22) = corners;
    vertices.at(23) = info;
    vertices.at(24) = radii;
    vertices.at(25) = width;
    vertices.at(26) = height;

    vertices.at(27) = positionX + width;
    vertices.at(28) = positionY + height;
    vertices.at(29) = 1;
    vertices.at(30) = 1;
    vertices.at(31) = corners;
    vertices.at(32) = info;
    vertices.at(33) = radii;
    vertices.at(34) = width;
    vertices.at(35) = height;
}

void QuadMesh::load(float positionX, float positionY, float width, float height, float textureWidth, float textureHeight, float textureX, float textureY, float textureRegionWidth, float textureRegionHeight, float info) {
    vertices.at(0) = positionX;
    vertices.at(1) = positionY;
    vertices.at(2) = textureX / textureWidth;
    vertices.at(3) = textureY / textureHeight;
    vertices.at(4) = corners;
    vertices.at(5) = info;
    vertices.at(6) = radii;
    vertices.at(7) = width;
    vertices.at(8) = height;

    vertices.at(9) = positionX + width;
    vertices.at(10) = positionY;
    vertices.at(11) = (textureX + textureRegionWidth) / textureWidth;
    vertices.at(12) = textureY / textureHeight;
    vertices.at(13) = corners;
    vertices.at(14) = info;
    vertices.at(15) = radii;
    vertices.at(16) = width;
    vertices.at(17) = height;

    vertices.at(18) = positionX;
    vertices.at(19) = positionY + height;
    vertices.at(20) = textureX / textureWidth;
    vertices.at(21) = (textureY + textureRegionHeight) / textureHeight;
    vertices.at(22) = corners;
    vertices.at(23) = info;
    vertices.at(24) = radii;
    vertices.at(25) = width;
    vertices.at(26) = height;

    vertices.at(27) = positionX + width;
    vertices.at(28) = positionY + height;
    vertices.at(29) = (textureX + textureRegionWidth) / textureWidth;
    vertices.at(30) = (textureY + textureRegionHeight) / textureHeight;
    vertices.at(31) = corners;
    vertices.at(32) = info;
    vertices.at(33) = radii;
    vertices.at(34) = width;
    vertices.at(35) = height;
}

void QuadMesh::updateMesh() {
    vbo.subData(vertices.data(), 4 * DataManager::quadLayout.getStride(), 0, GL_STATIC_DRAW);
}

void QuadMesh::render() {
    if(vertices.at(7) == 0 || vertices.at(8) == 0)
        return;
    vao.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void QuadMesh::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    this->radii = radii;
    this->corners = float((int)upperLeft << 3 | (int)lowerLeft << 2 | (int)upperRight << 1 | (int)lowerRight);
    vertices.at(4) = corners;
    vertices.at(6) = radii;
    vertices.at(13) = corners;
    vertices.at(15) = radii;
    vertices.at(22) = corners;
    vertices.at(24) = radii;;
    vertices.at(31) = corners;
    vertices.at(33) = radii;

    vbo.subData(vertices.data(), 4 * DataManager::quadLayout.getStride(), 0, GL_STATIC_DRAW);
}

QuadMesh::~QuadMesh() {
    vertices.clear();
}

void QuadMeshTriplet::init() {
    meshes[0].init();
    meshes[1].init();
    meshes[2].init();
}

void QuadMeshTriplet::loadPosition(float x, float y, float w, float h,
                                   float xx, float yy, float ww, float hh,
                                   float xxx, float yyy, float www, float hhh) {
    meshes[0].loadPosition(x, y, w, h);
    meshes[1].loadPosition(xx, yy, ww, hh);
    meshes[2].loadPosition(xxx, yyy, www, hhh);
}

void QuadMeshTriplet::loadPosition(float x, float y, float w, float h,
                                   float xx, float yy, float ww, float hh,
                                   float xxx, float yyy, float www, float hhh,
                                   float info) {
    meshes[0].loadPosition(x, y, w, h, info);
    meshes[1].loadPosition(xx, yy, ww, hh, info);
    meshes[2].loadPosition(xxx, yyy, www, hhh, info);
}

void QuadMeshTriplet::loadPosition(float x, float y, float w, float h) {
    meshes[0].loadPosition(x, y, w, h);
    meshes[1].loadPosition(x, y, w, h);
    meshes[2].loadPosition(x, y, w, h);
}

void QuadMeshTriplet::loadPosition(float x, float y, float w, float h, float info) {
    meshes[0].loadPosition(x, y, w, h, info);
    meshes[1].loadPosition(x, y, w, h, info);
    meshes[2].loadPosition(x, y, w, h, info);
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
    meshes[index].render();
}

void QuadMeshTriplet::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    this->radii = radii;
    meshes[0].setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    meshes[1].setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    meshes[2].setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
}

void QuadMeshTriplet::updateMesh() {
    meshes[0].updateMesh();
    meshes[1].updateMesh();
    meshes[2].updateMesh();
}