#pragma once

#include <OpenGL/Texture.h>
#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"
#include "../Text/UIText.h"

class UIImage : public UIComponent {
public:
    void init(float positionX = 0.0f, float positionY = 0.0f, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    void setColor(const UIColor& color);
    void setTexture(Texture* texture, float textureX, float textureY, float textureWidth, float textureHeight);
    void setTexture(Texture* texture);
    void setTextureCoords(float textureX, float textureY, float textureWidth, float textureHeight);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
    void setBounds(float positionX, float positionY, float width, float height) override;
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
    void updateMesh() override;

    QuadMesh mesh;
    Texture* texture;
    UIColor color;
    int mode = 0;
};