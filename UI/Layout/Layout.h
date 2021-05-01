#pragma once

#include <vector>

#include "../Components/UIComponent.h"

enum class LayoutDirection {
	ROW = 0,
	COLUMN
};

class Insets {
public:
	float left;
	float right;
	float top;
	float bottom;

	Insets();
	explicit Insets(float);
	Insets(float, float, float, float);
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

	Insets getInsets();
	void setInsets(Insets);

protected:
	Insets insets;
};