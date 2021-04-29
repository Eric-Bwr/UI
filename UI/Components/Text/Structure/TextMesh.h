#pragma once

#include <Buffer.h>

class UIText;
class FontType;
class Texture;
class UIColor;

class TextMesh {
public:
    TextMesh();
    void loadText(UIText *uiText, FontType* fontType);
    void render();
    ~TextMesh();
private:
    std::vector<float> vertices;
    unsigned int vertexCount;
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    Texture* texture;
};
