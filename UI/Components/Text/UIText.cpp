#include "UIText.h"
#include "Font.h"

UIText::UIText(const char *text, int fontSize, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = DataManager::defaultFont;
    this->fontSize = fontSize;
    this->positionX = 0;
    this->positionY = fontSize;
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->mode = mode;
    DataManager::loadText(this);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

UIText::UIText(const char *text, int fontSize, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = DataManager::defaultFont;
    this->fontSize = fontSize;
    this->positionX = 0;
    this->positionY = fontSize;
    this->width = width;
    this->height = height;
    this->mode = mode;
    DataManager::loadText(this);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

UIText::UIText(const char *text, int fontSize, float positionX, float positionY, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = DataManager::defaultFont;
    this->fontSize = fontSize;
    this->positionX = positionX;
    this->positionY = positionY + fontSize;
    this->width = width;
    this->height = height;
    this->mode = mode;
    DataManager::loadText(this);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

UIText::UIText(const char *text, Font* font, int fontSize, float positionX, float positionY, float width, float height, int mode) {
    this->type = UIComponentType::UITEXT;
    this->text = text;
    this->font = font;
    this->fontSize = fontSize;
    this->positionX = positionX;
    this->positionY = positionY + fontSize;
    this->width = width;
    this->height = height;
    this->mode = mode;
    DataManager::loadText(this);
    setRGBA(1.0, 1.0, 1.0, 1.0, COLOR_NORMALIZED);
}

void UIText::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    DataManager::loadText(this);
}

void UIText::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    DataManager::loadText(this);
}

void UIText::setBounds(float x, float y, float w, float h) {
	this->positionX = x;
	this->positionY = y;
	this->width = w;
	this->height = h;
	DataManager::loadText(this);
}

void UIText::setText(const char *text) {
    this->text = text;
    DataManager::loadText(this);
}

void UIText::setFont(Font* font) {
    this->font = font;
    DataManager::loadText(this);
}

void UIText::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    DataManager::loadText(this);
}

void UIText::setMode(int mode) {
    this->mode = mode;
    DataManager::loadText(this);
}