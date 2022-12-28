#include "UIImage.h"

void UIImage::init(float positionX, float positionY, float width, float height){
    type = UIComponentType::UIIMAGE;
    texture = nullptr;
    this->mesh.init();
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->color = COLOR_RED;
    this->mesh.load(positionX, positionY, width, height, 0);
    this->update = true;
}

void UIImage::setColor(const UIColor& color) {
    this->color = color;
    if (mode == 0)
        mode = 1;
    else if (mode == 2)
        mode = 3;
    mesh.loadPosition(positionX, positionY, width, height, mode);
    this->update = true;
}

void UIImage::setTexture(Texture *texture, float textureX, float textureY, float textureWidth, float textureHeight) {
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

void UIImage::setTexture(Texture *texture) {
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

void UIImage::setTextureCoords(float textureX, float textureY, float textureWidth, float textureHeight) {
    mesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), textureX, textureY, textureWidth, textureHeight, mode);
    this->update = true;
}

void UIImage::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UIImage::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UIImage::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    mesh.loadPosition(positionX, positionY, width, height);
    this->update = true;
}

void UIImage::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    mesh.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
    this->update = true;
}

void UIImage::updateMesh() {
    mesh.updateMesh();
}
