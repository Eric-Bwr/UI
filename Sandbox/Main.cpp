#include <iostream>
#include "../UI/Math/Vector.h"
#include "../UI/Math/Matrix.h"
#include "../UI/UIManager.h"
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

	UIComponent *component = new UIComponent();
	component->type = UIBUTTON;
	component->setPosition(20, 20);
	component->setSize(120, 80);

	UIManager *manager = new UIManager();
	manager->add(component);

    printf("%s", font.getErrorMessage().c_str());
    while(window.windowIsAlive()){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    manager->render();

	    if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.destroyWindow();
        window.updateWindow();
    }
}