#include "Layout.h"

void Layout::initLayout(float width, float height) {
	type = UIComponentType::UILAYOUT;
	insets = Insets();
	this->width = width;
	this->height = height;
}

void Layout::add(UIComponent *c) {
	components.emplace_back(c);
	adjust();
}

void Layout::add(UIComponent *component, LayoutPosition pos) {
	components.emplace_back(component);
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

void Layout::mouseButtonInput(int action) {
    for(auto component : components)
        component->mouseButtonInput(action);
}

void Layout::updateMesh() {
    for(auto component : components){
        if(component->update){
            component->updateMesh();
            component->update = false;
        }
    }
}

Insets Layout::getInsets() {
	return insets;
}

void Layout::setInsets(Insets insets) {
	this->insets = insets;
	adjust();
}

Insets::Insets() {
	left = 10;
	right = 10;
	top = 10;
	bottom = 10;
}

Insets::Insets(float value) {
	left = value;
	right = value;
	top = value;
	bottom = value;
}

Insets::Insets(float left, float right, float top, float bottom) {
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}
