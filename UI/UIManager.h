#pragma once

#include <Shader.h>
#include <Math/Matrix.h>
#include <chrono>

#include "Components/UIComponent.h"
#include "Components/Text/UIText.h"
#include "Components/Text/Font.h"
#include "Components/TextField/UITextField.h"
#include "Components/Button/UIButton.h"
#include "Components/Slider/UISlider.h"
#include "Components/SplitPane/UISplitPane.h"
#include "Layout/Layout.h"
#include "Layout/FlowLayout.h"
#include "Layout/BoxLayout.h"
#include "Layout/GridLayout.h"
#include "Layout/BorderLayout.h"

class UIManager {
public:
	void init(int width, int height);
	void add(UIComponent *component, int order = 0);
	void remove(UIComponent *component);
	void setSize(int width, int height);
	void keyInput(int key, int action, int mods);
	void charInput(unsigned int key);
	void mousePositionInput(double x, double y);
	void mouseButtonInput(int button, int action);
	void render();
    ~UIManager();
private:
    Mat4f ortho;
    Shader* textShader;
    Shader* quadShader;
	std::map<int, std::vector<UIComponent *>*> components;
	void renderComponent(UIComponent *);
	bool cursor = false;
    std::chrono::time_point<std::chrono::system_clock> start;
};