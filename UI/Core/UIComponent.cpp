#include "../Math/Vector.h"
#include "../Math/Matrix.h"

#include "UIComponent.h"

void UIComponent::setPosition(float x, float y) {
	this->x = x;
	this->y = y;

	updateModelMatrix();
}

void UIComponent::setPosition(Vec2f vec) {
	setPosition(vec.x, vec.y);
}

void UIComponent::setSize(float width, float height) {
	this->width = width;
	this->height = height;

	updateModelMatrix();
}

void UIComponent::updateModelMatrix() {
	this->modelMatrix = identityMatrix();
	this->modelMatrix.translate(x, y, 0);
	this->modelMatrix.scale(width, height, 1.0f);
}
