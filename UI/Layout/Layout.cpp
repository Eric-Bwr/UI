#include "Layout.h"

Layout::Layout(float _width, float _height) : UIComponent() {
	type = UIComponentType::UILAYOUT;
	insets = Insets();
	width = _width;
	height = _height;
}

void Layout::add(UIComponent *c) {
	components.emplace_back(c);
	adjust();
}


void Layout::add(UIComponent *c, LayoutPosition pos) {
	components.emplace_back(c);
	adjust();
}

void Layout::keyInput(int key, int action, int mods) {
    for(auto component : components)
        component->keyInput(key, action, mods);
}

void Layout::charInput(unsigned int key) {
    for(auto component : components)
        component->charInput(key);
}

void Layout::mousePositionInput(double x, double y) {
    for(auto component : components)
        component->mousePositionInput(x, y);
}

void Layout::mouseButtonInput(int button, int action) {
    for(auto component : components)
        component->mouseButtonInput(button, action);
}

Insets Layout::getInsets() {
	return insets;
}

void Layout::setInsets(Insets i) {
	insets = i;
	adjust();
}

Insets::Insets() {
	left = 10;
	right = 10;
	top = 10;
	bottom = 10;
}

Insets::Insets(float v) {
	left = v;
	right = v;
	top = v;
	bottom = v;
}

Insets::Insets(float l, float r, float t, float b) {
	left = l;
	right = r;
	top = t;
	bottom = b;
}
