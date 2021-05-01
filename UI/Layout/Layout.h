#pragma once

#include <vector>

#include "../Components/UIComponent.h"

enum class LayoutDirection {
	ROW = 0,
	COLUMN
};

class Layout : public UIComponent {
public:
	Layout(float, float);

	virtual void adjust() {}
	void add(UIComponent *);

    void keyInput(int key, int action, int mods) override;
    void charInput(unsigned int key) override;
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int button, int action) override;

	std::vector<UIComponent *> components;
};