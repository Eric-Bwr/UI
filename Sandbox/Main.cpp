#include <iostream>
#include "../UI/Math/Vector.h"
#include "../UI/Math/Matrix.h"
#include "Window/Window.h"
#include "../UI/Text/Font.h"

int main(){
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);
    Window window(windowSettings);
    Font font("C:/Windows/Fonts/Arial.ttf", 20);


    Mat4f mat = perspectiveMatrix(90, 1920, 1080, 0.1f, 100);
    mat.scale(10);

    std::cout << mat.toString();
    printf("%s", font.getErrorMessage().c_str());
    while(window.windowIsAlive()){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.destroyWindow();
        window.updateWindow();
    }
}