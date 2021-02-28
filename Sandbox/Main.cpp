#include <iostream>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include "../UI/UIManager.h"
#include "Window/Window.h"
#include "../UI/Text/Font.h"

#include <Buffer.h>
#include <OpenGL/include/Shader.h>

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

	Shader shader("../Assets/Shader/Test.glsl");
    std::cout << shader.getErrorMessage();
	VertexArrayObject vao;
	VertexBufferObjectLayout layout;
	layout.pushFloat(2);
    float vertices[] = {-1, 1, -1, -1, 1, 1, 1, -1};
	VertexBufferObject vbo(vertices, 8 * sizeof(float), GL_STATIC_DRAW);
	vao.addBuffer(vbo, layout);

    printf("%s", font.getErrorMessage().c_str());
    while(window.windowIsAlive()){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 0.0, 1.0, 1.0);
	    manager->render();
        shader.bind();
        font.texture->bind();
        if(glfwGetKey(window.getWindow(), GLFW_KEY_P)){
            font.texture->minNear();
            font.texture->magNear();
        }else{
            font.texture->minLinear();
            font.texture->magLinear();
        }
        vao.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	    if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}