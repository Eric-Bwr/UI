#pragma once

#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"

class UISplitPane: public UIComponent {
public:
	explicit UISplitPane(UIComponent *left = nullptr, UIComponent *right = nullptr, Orientation o = Orientation::HORIZONTAL);

    void setPosition(float positionX, float positionY) override;
    void setBounds(float positionX, float positionY, float width, float height) override;
    void setSize(float width, float height);
	void setLeft(UIComponent * left);
	void setRight(UIComponent *right);
	void setOrientation(Orientation orientation);
	void setDivider(float divider);

	inline UIComponent *getLeft(){ return left; }
	inline UIComponent *getRight(){ return right; }
	inline Orientation getOrientation(){ return orientation; }
	inline float getDivider() { return divider; }

    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int action) override;
    void keyInput(int key, int action, int mods) override;
    void charInput(unsigned int key) override;

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