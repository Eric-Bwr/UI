#include <Math/Vector.h>
#include <Math/Matrix.h>
#include "../UI/UIManager.h"
#include "Window/Window.h"
#include <Shader.h>
#include <thread>

int main() {
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);

    Window window(windowSettings);

    UIManager *manager = new UIManager(windowSettings->getWidth(), windowSettings->getHeight());

    Font font("C:/Windows/Fonts/Arial.ttf");
    const char* string = "The Quick black fox has been shot in the head by a 134 Minigun with a terrifying output of up to 100 Rounds per second when spooled up.\n        The 6 rotating barrels assist air cooling. ";
    UIText text(string, &font, 100, 0, 800, 1600, 800, UITextMode::RIGHT);
    manager->add(&text);
    int f = text.fontSize;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        manager->render();
        if(glfwGetKey(window.getWindow(), GLFW_KEY_UP) == GLFW_PRESS){
            f++;
            text.setFontSize(f);
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
        if(glfwGetKey(window.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS){
            f--;
            text.setFontSize(f);
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}