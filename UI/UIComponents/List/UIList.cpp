#include <iostream>
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
    autoHeight = height == -1;
}

void UIList::addEntry(const char *name, float spacing, const UIColorTriplet& bgColor) {
    float posY;
    entries.empty() ? posY = positionY : posY = entries.back().button->positionY + entries.back().spacing + entryHeight;
    if(!autoHeight && posY + entryHeight > height)
        return;
    entries.resize(entries.size() + 1);
    entries.back().button = new UIButton();
    entries.back().spacing = spacing;
    entries.back().button->init((char*)name, font, fontSize, UITextMode::CENTERED_VERTICAL_LEFT, positionX, posY, width, entryHeight);
    entries.back().button->setBackgroundColor(bgColor.standard, bgColor.hover, bgColor.pressed);
    entryValues.emplace_back(-1, -1);
    if(autoHeight){
        height = positionY - entries.back().button->positionY;
        background.height = height;
        this->update = true;
    }
}

void UIList::removeEntry(const char *name) {
    int index = -1;
    for (int i = 0; i < entries.size(); i++){
        if(entries.at(i).button->text.text == name)
            index = i;
    }
    if(index == -1)
        return;

    entries.erase(entries.begin() + index);
    entryValues.erase(entryValues.begin() + index);

    for (int i = 0; i < entries.size(); i++)
        entries.at(i).button->setPosition(positionX, positionY + (i == 0 ? 0.0f : entries.at(i).spacing) + i * entryHeight);
}

void UIList::setBackgroundColor(const UIColor &color) {
    background.color = color;
}

void UIList::setPosition(float positionX, float positionY) {
    float offsetX = positionX - this->positionX;
    float offsetY = positionY - this->positionY;
    this->positionX = positionX;
    this->positionY = positionY;
    background.setPosition(positionX, positionY);
    for (auto& entry : entries) {
        auto button = entry.button;
        button->setPosition(button->positionX + offsetX, button->positionY + offsetY);
    }
    this->update = true;
}

void UIList::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    background.setSize(width, height);
    for (int i = 0; i < entries.size(); i++){
        if(entries.at(i).button->positionY + entryHeight > height){
            entries.erase(entries.begin() + i, entries.end());
            entryValues.erase(entryValues.begin() + i, entryValues.end());
            break;
        }
        entries.at(i).button->setSize(width, entryHeight);
    }
    this->update = true;
}

void UIList::setBounds(float x, float y, float w, float h) {
    float offsetX = x - this->positionX;
    float offsetY = y - this->positionY;
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    if(h != -1){
        this->height = h;
        autoHeight = false;
    }
    background.setBounds(x, y, w, h);
    for (int i = 0; i < entries.size(); i++) {
        float posY = entries.at(i).button->positionY + offsetY;
        if(!autoHeight && posY + entryHeight > height){
            entries.erase(entries.begin() + i, entries.end());
            entryValues.erase(entryValues.begin() + i, entryValues.end());
            break;
        }
        entries.at(i).button->setBounds(entries.at(i).button->positionX + offsetX, posY, width, entryHeight);
    }
    this->update = true;
}

void UIList::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    background.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    this->radii = radii;
    this->upperLeft = upperLeft;
    this->lowerLeft = lowerLeft;
    this->upperRight = upperRight;
    this->lowerRight = lowerRight;
    //FIXME: recompute radii when removing entry
    if(!entries.empty())
        entries.at(0).button->setRadii(radii, upperLeft, false, upperRight, false);
    if(entries.size() > 1 && positionY + height == entries.back().button->positionY + entryHeight)
        entries.back().button->setRadii(radii, false, lowerLeft, false, lowerRight);
    this->update = true;
}

void UIList::mousePositionInput(double x, double y) {
    for (int i = 0; i < entries.size(); i++) {
        auto entry = entries.at(i).button;
        entry->mousePositionInput(x, y);
        if (callback != nullptr)
            if(entryValues[i].x != entry->pressed || entryValues[i].y != entry->hovered)
                callback(entry->pressed, entry->hovered, i);
        entryValues[i].x = entry->pressed;
        entryValues[i].y = entry->hovered;
    }
}

void UIList::mouseButtonInput(int action) {
    for (int i = 0; i < entries.size(); i++) {
        auto entry = entries.at(i).button;
        entry->mouseButtonInput(action);
        if (callback != nullptr)
            if(entryValues[i].x != entry->pressed || entryValues[i].y != entry->hovered)
                callback(entry->pressed, entry->hovered, i);
        entryValues[i].x = entry->pressed;
        entryValues[i].y = entry->hovered;
    }
}

void UIList::updateMesh() {
    background.updateMesh();
    for(auto& entry : entries)
        entry.button->updateMesh();
}

UIList::~UIList() {
    for(auto& entry : entries)
        delete entry.button;
}