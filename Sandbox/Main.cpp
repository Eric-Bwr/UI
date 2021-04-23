#include <iostream>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include "../UI/UIManager.h"
#include "Window/Window.h"
#include <Buffer.h>
#include <OpenGL/include/Shader.h>
#include "../UI/Components/UIText.h"
#include "../UI/Text/Font.h"
#include "../UI/Text/Structure/FontType.h"

int main() {
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);

    Window window(windowSettings);

    UIComponent *component = new UIComponent();
    component->type = UIBUTTON;
    component->setPosition(20, 20);
    component->setSize(120, 80);

    UIManager *manager = new UIManager();
    manager->add(component);

    Font font("C:/Windows/Fonts/Arial.ttf");
    std::cout << font.errorCode << "\n";
    UIText text("The quick fucker jumped over ya", &font, 50);
    Shader shader("../Assets/Shader/Test.glsl");
    std::cout << shader.getErrorMessage();
    Mat4f ortho = orthographicMatrix(0.0f, windowSettings->getWidth(), 0.0f, windowSettings->getHeight(), -1.0f, 1.0f);
    ortho.updateBuffer();
    shader.setUniformMatrix4f("ortho", ortho.getBuffer());
    Mat4f model;
    model.identity();
    model.translate(500, 500, 0);
    model.scale(12, 15, 0);
    shader.setUniformMatrix4f("model", model.getBuffer());
    VertexArrayObject vao;
    VertexBufferObjectLayout layout;
    layout.pushFloat(2);
    float vertices[] = {-1, 1, -1, -1, 1, 1, 1, -1};
    VertexBufferObject vbo(vertices, 8 * sizeof(float), GL_STATIC_DRAW);
    vao.addBuffer(vbo, layout);

    FontType fontType(&font, 20);

    // printf("%s", font.getErrorMessage().c_str());
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 1.0, 1.0);
        manager->render();
        shader.bind();
        fontType.texture->bind();
        if (glfwGetKey(window.getWindow(), GLFW_KEY_P)) {
            fontType.texture->minNear();
            fontType.texture->magNear();
        } else {
            fontType.texture->minLinear();
            fontType.texture->magLinear();
        }
        vao.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}