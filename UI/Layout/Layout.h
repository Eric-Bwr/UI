#pragma once

#include <vector>

#include "../Components/UIComponent.h"

enum class LayoutDirection {
	ROW = 0,
	COLUMN
};

class Layout: public UIComponent {
public:
	Layout(float, float);

	virtual void adjust();
	void add(UIComponent *);

	std::vector<UIComponent *> components;
};