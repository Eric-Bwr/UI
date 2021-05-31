#include "../UI/UIManager.h"
#include "Window/Window.h"
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

int main() {
    auto windowSettings = new WindowSettings;
    windowSettings->setWidth(1600);
    windowSettings->setHeight(800);
    windowSettings->setCentered(true);
    windowSettings->setTransparent(false);
    windowSettings->setShouldMultiSample(true);
    windowSettings->setSampleSize(2);

    Window window(windowSettings);

    glfwSetFramebufferSizeCallback(window.getWindow(), frameBufferSize);
    glfwSetKeyCallback(window.getWindow(), keyCallback);
    glfwSetCharCallback(window.getWindow(), charCallback);
    glfwSetCursorPosCallback(window.getWindow(), mousePositionCallback);
    glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);

    manager.init(windowSettings->getWidth(), windowSettings->getHeight(), true);

    Font font("C:/Windows/Fonts/Arial.ttf");
    char *string = "Crocs, Inc. is an American company based in Niwot, Colorado that manufactures and markets the Crocs brand of foam clogs.\nThe company has since established a considerable following with American middle school and high school students, with many opting for Crocs to use as school shoes for the school day.";

    Font farCry("../Assets/Fonts/FarCry.ttf");
    char *farCryString = "g";
    UIText farCryText(farCryString, &farCry, 200, 0, 0, 1600, 800, LEFT);
	manager.add(&farCryText, 6);

	UITexture texture("../Assets/Textures/Button.png");
	UIButton test(500, 100, 198 * 4, 18 * 4);
	test.setBackgroundTexture(&texture, 0, 18 * 2, 198, 18, 0, 18, 198, 18, 0, 0, 198, 18);
	test.setText("Test Button", &font, 50);
	manager.add(&test, 5);

	UIImage image(500, 500, 200, 200);
	image.setTexture(&texture);
	image.setColor(COLOR_CYAN);
	manager.add(&image, 5);

	UITextField textField("Default", 700, 500, 198 * 4, 18 * 4, 10);
	UITexture fieldTex("../Assets/Textures/TextField.png");
	textField.setBackgroundTexture(&fieldTex, 0, 0, 108, 19, 0, 19, 108, 19, 0, 19 * 2, 108, 19);
	manager.add(&textField, 5);

	UITextArea textArea(100, 100, 1400, 600);
	textArea.setFontSize(50);
	textArea.setText(string);
	manager.add(&textArea, 11);

	UISlider slider(1000, 300, 500, 50, 5, -10, 10);
	slider.setRadii(20);
	UITexture sliderTex("../Assets/Textures/Slider.png");
	slider.setTexture(&sliderTex);
	slider.setBackgroundCoords(0, 0, 300, 35, 0, 35, 300, 35, 0, 35, 300, 35);
	slider.setSlideCoords(0, 0, 300, 35, 0, 35 * 2, 300, 35, 0, 35 * 2, 300, 35);
	slider.setDragCoords(300, 0, 40, 40, 300, 40, 40, 40, 340, 0, 40, 40);
	manager.add(&slider);

	UIText sliderText("Slider Value: ", 50, 1000, 400, 1000, 100, UITextMode::LEFT);
	manager.add(&sliderText, 6);
	std::string sliderString("Slider Value: ");

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


	UIButton btn1;
	btn1.bgColor = COLOR_YELLOW;
	btn1.setSize(400, 1200);
	UIButton btn2;
	btn1.bgColor = COLOR_YELLOW;
	btn1.setSize(400, 1200);

   /* UISplitPane splitPane(0, 0, 1600, 800, &btn1, &test, Orientation::HORIZONTAL);
    UITexture splitPaneTexture("../Assets/Textures/SplitPane.png");
    splitPane.setDividerTexture(&splitPaneTexture, 0, 0, 10, 800);
    splitPane.setDividerColor({0, 0, 0, 1}, {0.1, 0.1, 0.1, 1}, {0.3, 0.3, 0.3, 1});
    manager.add(&splitPane, 10);
*/
	UIText text1(string, &font, 40, 0, 0, 1600, 800, UITextMode::CENTERED_HORIZONTAL);

	UIScrollbar scrollbar(&text1, 40, 300, 400, 400, Orientation::VERTICAL);
	scrollbar.setRadii(5);

	manager.add(&scrollbar);

	UISwitch sw(100, 100, 60, 30);
	sw.setCircular(true);

	UISwitch sw2(100, 150, 90, 25);
	sw2.setCircular(true);
	sw2.setSwitchSize(1.6);

	UISwitch sw3(100, 200, 50, 20);
	sw3.setCircular(true);
	sw3.setSwitchSize(0.7);

	manager.add(&sw);
	manager.add(&sw2);
	manager.add(&sw3);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        manager.render();
        // sliderText.setText((sliderString + std::to_string(slider.getValue())).data());
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}