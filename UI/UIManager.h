#pragma once

#include <Shader.h>
#include <Math/Matrix.h>

#include "Components/UIComponent.h"
#include "Components/Text/UIText.h"
#include "Components/Text/Font.h"
#include "Components/Button/UIButton.h"

class UIManager {
public:
	void init(int width, int height);
	void add(UIComponent *component, int order = 0);
	void remove(UIComponent *component);
	void setSize(int width, int height);
	void render();
    ~UIManager();
private:
    Mat4f ortho;
    Shader* textShader;
    Shader* quadShader;
	std::map<int, std::vector<UIComponent *>*> components;
};