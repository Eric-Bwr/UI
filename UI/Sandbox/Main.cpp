#include <iostream>
#include "Window/Window.h"

int main(){
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);
    Window window(windowSettings);

    while(window.windowIsAlive()){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.destroyWindow();
        window.updateWindow();
    }
}