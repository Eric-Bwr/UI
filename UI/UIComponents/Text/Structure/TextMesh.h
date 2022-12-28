#pragma once

#include <OpenGL/Buffer.h>
#include <OpenGL/Texture.h>

class UIText;
class FontType;
class UIColor;

struct Word {
    std::vector<char> characters;
    float width = 0.0f;
    float spaceWidth = 0.0f;
};

struct Line {
    std::vector<Word> words;
    float lineWidth = 0.0f;
};

class TextMesh {
public:
    void init();
    void loadTextStructure(UIText* uiText);
    void loadText(UIText* uiText);
    void render();
    ~TextMesh();
    std::vector<Line> lines;
private:
    std::vector<float> vertices;
    unsigned int vertexCount;
    VertexArrayObject vao;
    VertexBufferObject vbo;
    Texture texture;
};
