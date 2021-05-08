#pragma once

#include "DataManager.h"

class QuadMesh {
public:
    QuadMesh();
    void loadPosition(float positionX, float positionY, float width, float height);
    void load(float positionX, float positionY, float width, float height, float info);
    void load(float positionX, float positionY, float width, float height, float textureWidth, float textureHeight, float textureX, float textureY, float textureRegionWidth, float textureRegionHeight, float info);
    void render();
    ~QuadMesh();
    VertexArrayObject vao;
    VertexBufferObject vbo;
private:
    std::vector<float> vertices;
};

class QuadMeshTriplet {
public:
    void loadPosition(float x, float y, float w, float h,
                      float xx, float yy, float ww, float hh,
                      float xxx, float yyy, float www, float hhh);
    void loadPosition(float x, float y, float w, float h);
    void load(float x, float y, float w, float h,
              float xx, float yy, float ww, float hh,
              float xxx, float yyy, float www, float hhh, float info);
    void load(float x, float y, float w, float h, float info);
    void load(float x, float y, float w, float h,
              float xx, float yy, float ww, float hh,
              float xxx, float yyy, float www, float hhh,
              float info, float textureWidth, float textureHeight,
              float texX, float texY, float texW, float texH,
              float texXX, float texYY, float texWW, float texHH,
              float texXXX, float texYYY, float texWWW, float texHHH);
    void load(float x, float y, float w, float h,
              float info, float textureWidth, float textureHeight,
              float texX, float texY, float texW, float texH,
              float texXX, float texYY, float texWW, float texHH,
              float texXXX, float texYYY, float texWWW, float texHHH);
    void render(int index);
private:
    QuadMesh meshes[3];
};