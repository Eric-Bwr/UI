#pragma once

#include <map>
#include <vector>

#include "Core/UIComponent.h"

class UIManager {
public:
	UIManager();
	~UIManager();

	void add(UIComponent *component, int order=0);
	void remove(UIComponent *component);

	void render();
private:
	std::map<int, std::vector<UIComponent *>*> components;
};
