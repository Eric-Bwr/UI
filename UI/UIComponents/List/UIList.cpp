#include "UIList.h"

void UIList::init(float positionX, float positionY, float width, float height, int fontSize, Font* font){
    type = UIComponentType::UILIST;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->fontSize = fontSize;
    this->font = font;
    background.init(positionX, positionY, width, height);
    background.updateMesh();
    background.color = {0.5, 0.5, 0.5, 0.5};
    this->update = true;
}

void UIList::addEntry(const char *name) {
    entries.resize(entries.size() + 1);
    entries.back() = new UIButton();
    entries.back()->init((char*)name, font, fontSize, UITextMode::CENTERED_VERTICAL_LEFT, 0, float(entries.size() - 1) * entryHeight, width, entryHeight);
}

void UIList::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    background.setPosition(positionX, positionY);
    this->update = true;
}

void UIList::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    background.setSize(width, height);
    this->update = true;
}

void UIList::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    background.setBounds(x, y, w, h);
    this->update = true;
}

void UIList::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    background.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    this->update = true;
}

void UIList::updateMesh() {
    background.updateMesh();
    for(auto & entry : entries){
        entry->updateMesh();
    }
}