#pragma once

#include <Texture.h>
#include "DataManager.h"

class QuadMesh {
public:
    QuadMesh();
    void loadPosition(float positionX, float positionY, float width, float height);
    void load(float positionX, float positionY, float width, float height, float info);
    void load(float positionX, float positionY, float width, float height, float textureWidth, float textureHeight, float textureX, float textureY, float textureRegionWidth, float textureRegionHeight, float info);
    void render();
    ~QuadMesh();
private:
    std::vector<float> vertices;
    unsigned int vertexCount;
    VertexArrayObject vao;
    VertexBufferObject vbo;
};