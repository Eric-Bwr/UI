#pragma once

#include <map>
#include <vector>

#include "Core/UIComponent.h"

class UIManager {
public:
	UIManager(int width, int height);
	void add(UIComponent *component, int order=0);
	void remove(UIComponent *component);
	static void setSize(int width, int height);
	void render();
    ~UIManager();
private:
	std::map<int, std::vector<UIComponent *>*> components;
};