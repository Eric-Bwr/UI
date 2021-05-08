#pragma once

#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UISplitPane: public UIComponent {
public:
	explicit UISplitPane(UIComponent *l = nullptr, UIComponent *r = nullptr, Orientation o = Orientation::HORIZONTAL);

	void mousePositionInput(double, double) override;
	void mouseButtonInput(int, int) override;
	void keyInput(int key, int action, int mods) override;
	void charInput(unsigned int key) override;

	void setPosition(float, float) override;
	void setBounds(float, float, float, float) override;
	void setSize(float, float);

	void setLeft(UIComponent *);
	void setRight(UIComponent *);
	void setOrientation(Orientation);
	void setDivider(float);

	UIComponent *getLeft();
	UIComponent *getRight();
	Orientation getOrientation();
	float getDivider();

	QuadMesh mesh;
	UIColor dividerColor;
private:
	void calc();

	Orientation orientation;
	UIComponent *left;
	UIComponent *right;
	float divider;

	bool dragging;
	bool hovered;
	float divWidth;
};