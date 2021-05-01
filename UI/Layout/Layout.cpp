#include "Layout.h"

/* TODO: BorderLayout, GridLayout, UIColor, Button */

Layout::Layout(float _width, float _height) : UIComponent() {
	type = UIComponentType::UILAYOUT;
	width = _width;
	height = _height;
}

void Layout::add(UIComponent *c) {
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
