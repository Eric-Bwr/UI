#pragma once

#include <OpenGL/Texture.h>
#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"
#include "../Text/UIText.h"

class UICircularBar : public UIComponent {
public:
    explicit UICircularBar(float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT);
    UICircularBar(float positionX, float positionY, float width, float height);

    void setColor(const UIColor& color);
    void setTexture(Texture* texture, float textureX, float textureY, float textureWidth, float textureHeight);
    void setTexture(Texture* texture);
    void setTextureCoords(float textureX, float textureY, float textureWidth, float textureHeight);
    void setPosition(float positionX, float positionY) override;
    void setBounds(float positionX, float positionY, float width, float height) override;
    void setSize(float width, float height);
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
    void setArcs(float start, float first, float second, float end);
    void setDiameters(float outerOD, float outerID, float innerOD, float innerID);
    void setProgress(float progress);
    void setLineThickness(float lineThickness);
    void setNeedleDot(float ID, float OD);
    void setLineColor(const UIColor& color);
    void setDotColor(const UIColor& color);
    void setAngle1Color(const UIColor& color);
    void setAngle2Color(const UIColor& color);
    void setAngle3Color(const UIColor& color);
    void updateMesh() override;

    QuadMesh mesh;
    Texture* texture;
    UIColor color;
    float progress, lineThickness = 0.015;
    Vec2f needleDot;
    Vec4f arcs;
    Vec4f diameters;
    UIColor lineColor;
    UIColor dotColor;
    UIColor colorAngle1;
    UIColor colorAngle2;
    UIColor colorAngle3;
private:
    int mode = 0;
};