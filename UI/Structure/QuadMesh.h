#pragma once

#include <Texture.h>
#include "DataManager.h"

class QuadMesh {
public:
    QuadMesh();
    void load(float positionX, float positionY, float width, float height, float info);
    void render();
    void reset();
    ~QuadMesh();
private:
    std::vector<float> vertices;
    unsigned int vertexCount;
    VertexArrayObject vao;
    VertexBufferObject vbo;
};