#include <iostream>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include "../UI/UIManager.h"
#include "Window/Window.h"
#include <Shader.h>
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

    UIManager *manager = new UIManager(windowSettings->getWidth(), windowSettings->getHeight());
    manager->add(component);

    Shader shader("../Assets/Shader/Test.glsl");

    Font font("C:/Windows/Fonts/Arial.ttf");
    UIText text("The quick brown fucker jumped over ya", &font, 400, 300, 300);
    FontType fontType(&font, 20);

    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 1.0, 1.0);
        manager->render();
        shader.bind();
        fontType.texture->bind();
        text.textMesh.render();
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}