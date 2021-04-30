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

void Layout::adjust() {}