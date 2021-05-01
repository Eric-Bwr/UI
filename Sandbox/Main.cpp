#include "../UI/UIManager.h"
#include "Window/Window.h"
#include <thread>

UIManager manager;

static void frameBufferSize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    manager.setSize(width, height);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    manager.keyInput(key, action, mods);
}

static void charCallback(GLFWwindow* window, unsigned int key){
    manager.charInput(key);
}

static void mousePositionCallback(GLFWwindow* window, double x, double y){
    manager.mousePositionInput(x, y);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    manager.mouseButtonInput(button, action);
}

int main() {
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);

    Window window(windowSettings);
    glfwSetFramebufferSizeCallback(window.getWindow(), frameBufferSize);
    glfwSetKeyCallback(window.getWindow(), keyCallback);
    glfwSetCharCallback(window.getWindow(), charCallback);
    glfwSetCursorPosCallback(window.getWindow(), mousePositionCallback);
    glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);

    manager.init(windowSettings->getWidth(), windowSettings->getHeight());

   Font font("C:/Windows/Fonts/Arial.ttf");

   const char* string = "  The Quick black fox has been shot in the head by a 134 Minigun with a terrifying output of up to 100 Rounds per second when spooled up.\nThe 6 rotating barrels assist air cooling. ";
   //UIText text(string, &font, 20, 0, 0, 200, 100, UITextMode::LEFT);
   //text.a = 0.75f;
   //int f = text.fontSize;

    UIButton test(200, 200, 500, 300);
    test.setText(string, &font, 50);
    test.fgColor = COLOR_BLACK;
    manager.add(&test);

    /*
    Texture tex("../Assets/Textures/stone");
    tex.clampEdge();
    tex.nearest();
    tex.load(true); */


    /* Layout Test */
	/* manager.add(&text);
	manager.add(&button); */

	/* Test 1 */

	UIButton button(180, 50);
	UIButton button1(180, 50);
	UIButton button2(180, 50);
	UIButton button3(180, 50);
	UIButton button4(180, 50);
	UISlider slider(220, 20);

	/* Test 2 */
	/*
	UIButton button(0, 0, 260, 140);
	UIButton button1(0, 0, 260, 180);
	UIButton button2(0, 0, 160, 140);
	UIButton button3(0, 0, 260, 240);
	UIButton button4(0, 0, 160, 140);
	UIButton button5(0, 0, 260, 140);
	UIButton button6(0, 0, 160, 170);
	UIButton button7(0, 0, 260, 140);
	UIButton button8(0, 0, 260, 140);
	UIButton button9(0, 0, 160, 170);
	UIButton button10(0, 0, 260, 140); */

	BoxLayout layout(1600, 800);

	layout.add(&button);
	layout.add(&button1);
	layout.add(&button2);
	layout.add(&button3);
	layout.add(&button4);
	layout.add(&slider);

	manager.add(&layout);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        manager.render();
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}