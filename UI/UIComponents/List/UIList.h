#pragma once

#include <OpenGL/Texture.h>
#include "../Image/UIImage.h"
#include "../Scrollbar/UIScrollbar.h"
#include "../Button/UIButton.h"
#include "../../UIStructure/QuadMesh.h"
#include "../Text/UIText.h"

class UIList : public UIComponent {
public:
    void init(float positionX = 0.0f, float positionY = 0.0f, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, int fontSize = 10, Font* font = DataManager::defaultFont);
    void addEntry(const char* name);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
    void setBounds(float positionX, float positionY, float width, float height) override;
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
    void updateMesh() override;
    UIImage background;
    std::vector<UIButton*> entries;
    Font* font;
    int fontSize = 10;
    float entryHeight = 30.0f;
};