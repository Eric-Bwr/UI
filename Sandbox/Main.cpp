#include "../UI/UIManager.h"
#include "Window/Window.h"
#include <thread>

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

    Window window(windowSettings);
    glfwSetFramebufferSizeCallback(window.getWindow(), frameBufferSize);
    glfwSetKeyCallback(window.getWindow(), keyCallback);
    glfwSetCharCallback(window.getWindow(), charCallback);
    glfwSetCursorPosCallback(window.getWindow(), mousePositionCallback);
    glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);

    manager.init(windowSettings->getWidth(), windowSettings->getHeight());

    Font font("C:/Windows/Fonts/Arial.ttf");

    const char *string = "Crocs, Inc. is an American company based in Niwot, Colorado that manufactures and markets the Crocs brand of foam clogs.\nThe company has since established a considerable following with American middle school and high school students, with many opting for Crocs to use as school shoes for the school day.";
    UIText text(string, &font, 50, 0, 0, 1600, 800, UITextMode::CENTERED_HORIZONTAL);
    manager.add(&text, 4);

    Texture tex("../Assets/Textures/Button");
    tex.clampEdge();
    tex.nearest();
    tex.load(true);


    /* Layout Test */
    /* manager.add(&text);
    manager.add(&button); */

    /* Test 1 */
    UIButton test(200, 300, 198 * 4, 18 * 4);
    test.setTexture(&tex, 0, 18 * 2, 198, 18, 0, 18, 198, 18, 0, 0, 198, 18);
    test.setText("Test Button", &font, 50);
    test.fgColor = COLOR_WHITE;
    manager.add(&test, 5);

    UITextField textField("Default", 700, 500, 198 * 4, 18 * 4);
    textField.fgColor = COLOR_WHITE;
    textField.cursorColor = COLOR_WHITE;
    Texture fieldTex("../Assets/Textures/TextField");
    fieldTex.load(true);
    textField.setTexture(&fieldTex);
    manager.add(&textField, 5);

    UISlider slider(1000, 300, 500, 50);
    slider.bgColor.setRGBA(80, 80, 80, 255, COLOR_DECIMAL);
    slider.dragColor.setRGBA(198, 198, 198, 255, COLOR_DECIMAL);
    slider.setFloating(false);
    manager.add(&slider);

    UIText sliderText("Slider Value: ", 50, 1000, 400, 1000, 100, UITextMode::LEFT);
    manager.add(&sliderText, 6);
    std::string sliderString("Slider Value: ");

    UIButton button(180, 50);
    UIButton button1(180, 50);
    UIButton button2(180, 50);
    UIButton button3(180, 50);
    UIButton button4(180, 50);
    //UISlider slider(220, 7);
    //slider.setFloating(false);

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

    //GridLayout layout(0, 3, 1600, 800);
//
    //layout.add(&button);
    //layout.add(&button1);
    //layout.add(&button2);
    //layout.add(&button3);
    //layout.add(&button4);
    //layout.add(&slider);

    //manager.add(&layout);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (window.windowIsAlive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        manager.render();
        sliderText.setText((sliderString + std::to_string(slider.getValue())).c_str());
        if (glfwGetKey(window.getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
            text.setFontSize(text.fontSize + 1);
            test.setFontSize(test.text.fontSize + 1);
            textField.text.setFontSize(textField.text.fontSize + 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            text.setFontSize(text.fontSize - 1);
            test.setFontSize(test.text.fontSize - 1);
            textField.text.setFontSize(textField.text.fontSize - 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
            window.setWindowIsAlive(false);
        window.updateWindow();
    }
    window.destroyWindow();
}