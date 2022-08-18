#pragma once

#include <OpenGL/Shader.h>
#include <Math/Matrix.h>
#include <chrono>

#include "UIComponents/UIComponent.h"
#include "UIComponents/Text/UIText.h"
#include "UIComponents/Text/Font.h"
#include "UIComponents/TextField/UITextField.h"
#include "UIComponents/TextArea/UITextArea.h"
#include "UIComponents/Button/UIButton.h"
#include "UIComponents/Image/UIImage.h"
#include "UIComponents/Slider/UISlider.h"
#include "UIComponents/SplitPane/UISplitPane.h"
#include "UIComponents/Scrollbar/UIScrollbar.h"
#include "UIComponents/Switch/UISwitch.h"
#include "UILayout/Layout.h"
#include "UILayout/FlowLayout.h"
#include "UILayout/BoxLayout.h"
#include "UILayout/GridLayout.h"
#include "UILayout/BorderLayout.h"

class UIManager {
public:
	void init(int width, int height, bool scaleOnResize = false);
	void add(UIComponent *component, int order = 0);
	void remove(UIComponent *component);
	void setSize(int width, int height);
	void keyInput(int key, int action, int mods);
	void charInput(unsigned int key);
	void mousePositionInput(double x, double y);
	void mouseButtonInput(int button, int action);
	void render();
    ~UIManager();
    double mouseX = 0, mouseY = 0;
    int width, height;
private:
    Mat4f ortho;
    Shader* textShader;
    Shader* quadShader;
	std::map<int, std::vector<UIComponent *>*> components;
	void renderComponent(UIComponent *component);
	bool cursor = false, scaleOnResize = false;
    std::chrono::time_point<std::chrono::system_clock> start;
};