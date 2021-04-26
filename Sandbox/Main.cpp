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

    Mat4f mat = orthographicMatrix(0.0f, windowSettings->getWidth(), windowSettings->getHeight(), 0.0, -1.0, 1.0);
    Shader shader("../Assets/Shader/Test.glsl");
    shader.setUniformMatrix4f("ortho", mat.getBuffer());

    Font font("C:/Windows/Fonts/Arial.ttf");
    UIText text("The Quick black fox has been shot in the head by a 134 Minigun with a terrifying output of up to 100 Rounds per second when spooled up.\nThe 6 rotating barrels assist air cooling.", &font, 100, 50, 700, 1600, 700);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        manager->render();
        shader.bind();
        text.textMesh.render();
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}