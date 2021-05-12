#include "../UI/UIManager.h"
#include "Window/Window.h"
#include <thread>
#include <iostream>

UIManager manager;

static void frameBufferSize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
	manager.setSize(width, height);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    manager.keyInput(key, action, mods);
}

static void charCallback(GLFWwindow *window, unsigned int key) {
    manager.charInput(key);
}

static void mousePositionCallback(GLFWwindow *window, double x, double y) {
    manager.mousePositionInput(x, y);
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    manager.mouseButtonInput(button, action);
}

static void callback(bool pressed, bool hovered){
    std::cout << "Pressed: " << pressed << " Hovered: " << hovered << "\n";
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
    const char *string = "Crocs, Inc. is an American company based in Niwot, Colorado that manufactures and markets the Crocs brand of foam clogs.\nThe company has since established a considerable following with American middle school and high school students, with many opting for Crocs to use as school shoes for the school day.";
    UIText text(string, &font, 20, 0, 0, 1600, 800, UITextMode::CENTERED_HORIZONTAL);
    manager.add(&text, 4);

    UITexture texture("../Assets/Textures/Button.png");
    UIButton test(500, 100, 198 * 4, 18 * 4);
    test.setTexture(&texture, 0, 18 * 2, 198, 18, 0, 18, 198, 18, 0, 0, 198, 18);
    test.setText("Test Button", &font, 50);
    test.fgColor = COLOR_WHITE;
    manager.add(&test, 5);

    UITextField textField("Default", 700, 500, 198 * 4, 18 * 4, 10);
    textField.fgColor = COLOR_WHITE;
    textField.cursorColor = COLOR_WHITE;
    UITexture fieldTex("../Assets/Textures/TextField.png");
    textField.setCallback(callback);
    textField.setTexture(&fieldTex, 0, 0, 108, 19, 0, 19, 108, 19, 0, 19 * 2, 108, 19);
    manager.add(&textField, 5);

    UISlider slider(1000, 300, 500, 50, 5, -10, 10);
    UITexture sliderTex("../Assets/Textures/Slider.png");
    slider.setTexture(&sliderTex, 0, 0, 300, 35, 0, 35, 300, 35, 0, 35, 300, 35);
    slider.setSlideCoords(0, 0, 300, 35, 0, 35 * 2, 300, 35, 0, 35 * 2, 300, 35);
    slider.setDragCoords(300, 0, 40, 40, 300, 40, 40, 40, 340, 0, 40, 40);
    slider.bgColor.setRGBA(80, 80, 80, 255, COLOR_DECIMAL);
    slider.dragColor.setRGBA(198, 198, 198, 255, COLOR_DECIMAL);
    slider.setFloating(false);
    manager.add(&slider);

    UIText sliderText("Slider Value: ", 50, 1000, 400, 1000, 100, UITextMode::LEFT);
    manager.add(&sliderText, 6);
    std::string sliderString("Slider Value: ");
/*
    UIButton button;
    UIButton button1;
    UIButton button2;
    UIButton button3;

    button.bgColor = COLOR_RED;

    GridLayout layout(windowSettings->getWidth(), windowSettings->getHeight());
    layout.setColumns(2);
    layout.add(&button);
    layout.add(&button1);
    layout.add(&button2);
    layout.add(&button3);

    manager.add(&layout);
*/

	UIButton btn1;
	btn1.bgColor = COLOR_YELLOW;
	btn1.setSize(400, 1200);

	string = "a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\nq\nr\ns\nt\nu\nv\nx\ny\nz\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n";
	UIText text1(string, &font, 20, 0, 0, 400, 1600, UITextMode::CENTERED_HORIZONTAL);
	text1.fontSize = 40;

	UIScrollbar scrollbar(&text1);
	scrollbar.setBounds(40, 80, 400, 400);

	manager.add(&scrollbar);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        manager.render();
        sliderText.setText((sliderString + std::to_string(slider.getValue())).c_str());
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}