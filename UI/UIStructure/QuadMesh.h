#pragma once

#include "DataManager.h"
#include "UI/UIColor.h"

struct UIColorTriplet {
    UIColorTriplet& operator=(const UIColor& color);
    UIColor standard, hover, pressed;
};

class QuadMesh {
public:
    void init();
    void loadPosition(float positionX, float positionY, float width, float height);
    void loadPosition(float positionX, float positionY, float width, float height, float info);
    void load(float positionX, float positionY, float width, float height, float info);
    void load(float positionX, float positionY, float width, float height, float textureWidth, float textureHeight, float textureX, float textureY, float textureRegionWidth, float textureRegionHeight, float info);
    void updateMesh();
    void render();
    ~QuadMesh();
    void setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight);
    float radii = 0, corners = float((int)0 << 3 | (int)0 << 2 | (int)0 << 1 | (int)0);
    VertexArrayObject vao;
    VertexBufferObject vbo;
private:
    std::vector<float> vertices;
};

class QuadMeshTriplet {
public:
    void init();
    void loadPosition(float x, float y, float w, float h,
                      float xx, float yy, float ww, float hh,
                      float xxx, float yyy, float www, float hhh);
    void loadPosition(float x, float y, float w, float h,
                      float xx, float yy, float ww, float hh,
                      float xxx, float yyy, float www, float hhh,
                      float info);
    void loadPosition(float x, float y, float w, float h);
    void loadPosition(float x, float y, float w, float h, float info);
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
    void updateMesh();
    void render(int index);
    void setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight);
    float radii = 0;
private:
    QuadMesh meshes[3];
};