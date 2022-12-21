#include "UICircularBar.h"

void UICircularBar::init(float positionX, float positionY, float width, float height){
    type = UIComponentType::UICIRCULARBAR;
    this->mesh.init();
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->color = COLOR_RED;
    mesh.load(positionX, positionY, width, height, 0);
    arcs = {45.0 / 360.0, 90.0 / 360.0, 135.0 / 360.0, 270.0 / 360.0};
    diameters = {0.9, 0.8, 0.78, 0.6};
    needleDot = {0.04, 0.05};
    lineColor = {0.8, 0.2, 0.2, 0.9};
    dotColor = {0.0, 0.0, 0.0, 0.0};
    colorAngle1 = {1.0, 0.0, 0.0, 1.0};
    colorAngle2 = {1.0, 1.0, 0.0, 1.0};
    colorAngle3 = {0.0, 1.0, 0.0, 1.0};
    progress = 0.5;
    this->update = true;
}

void UICircularBar::setColor(const UIColor& color) {
    this->color = color;
    if (mode == 0)
        mode = 1;
    else if (mode == 2)
        mode = 3;
    mesh.loadPosition(positionX, positionY, width, height, mode);
    this->update = true;
}

void UICircularBar::setTexture(Texture *texture, float textureX, float textureY, float textureWidth, float textureHeight) {
    this->texture = texture;
    if(texture == nullptr) {
        if (mode == 3)
            mode = 1;
        else if (mode == 2)
            mode = 0;
    }else {
        if (mode == 0)
            mode = 2;
        else if (mode == 1)
            mode = 3;
    }
    mesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), textureX, textureY, textureWidth, textureHeight, mode);
    this->update = true;
}

void UICircularBar::setTexture(Texture *texture) {
    this->texture = texture;
    if(texture == nullptr) {
        if (mode == 3)
            mode = 1;
        else if (mode == 2)
            mode = 0;
    }else {
        if (mode == 0)
            mode = 2;
        else if (mode == 1)
            mode = 3;
    }
    mesh.load(positionX, positionY, width, height, mode);
    this->update = true;
}

void UICircularBar::setTextureCoords(float textureX, float textureY, float textureWidth, float textureHeight) {
    mesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), textureX, textureY, textureWidth, textureHeight, mode);
    this->update = true;
}

void UICircularBar::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UICircularBar::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UICircularBar::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UICircularBar::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    mesh.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    this->update = true;
}

void UICircularBar::setArcs(float start, float first, float second, float end) {
    arcs = {start / 360.0f, first / 360.0f, second / 360.0f, end / 360.0f};
}

void UICircularBar::setDiameters(float outerOD, float outerID, float innerOD, float innerID) {
    diameters = {outerOD, outerID, innerOD, innerID};
}

void UICircularBar::setProgress(float progress) {
    progress = progress * (arcs.w - arcs.x) / 1.0f + arcs.x;
    this->progress = progress;
}

void UICircularBar::setLineThickness(float lineThickness) {
    this->lineThickness = lineThickness;
}

void UICircularBar::setNeedleDot(float ID, float OD) {
    needleDot = {ID, OD};
}

void UICircularBar::setLineColor(const UIColor &color) {
    lineColor = color;
}

void UICircularBar::setDotColor(const UIColor &color) {
    dotColor = color;
}

void UICircularBar::setAngle1Color(const UIColor& color) {
    colorAngle1 = color;
}

void UICircularBar::setAngle2Color(const UIColor& color) {
    colorAngle2 = color;
}

void UICircularBar::setAngle3Color(const UIColor& color) {
    colorAngle3 = color;
}

void UICircularBar::updateMesh() {
    mesh.updateMesh();
}
