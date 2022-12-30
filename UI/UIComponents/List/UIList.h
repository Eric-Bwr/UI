#pragma once

#include <OpenGL/Texture.h>
#include "../Image/UIImage.h"
#include "../Scrollbar/UIScrollbar.h"
#include "../Button/UIButton.h"
#include "../../UIStructure/QuadMesh.h"
#include "../Text/UIText.h"

const UIColorTriplet COLOR_LIST = UIColorTriplet(UIColor(0x808080), UIColor(0xAAAAAA), UIColor(0xDDDDDD));

struct UIListButton {
    UIButton* button;
    float spacing;
};

class UIList : public UIComponent {
public:
    void init(float positionX = 0.0f, float positionY = 0.0f, float width = DEFAULT_WIDTH, float height = AUTO_HEIGHT, int fontSize = 10, Font* font = DataManager::defaultFont);
    void addEntry(const char* name, float spacing = 0.0f, const UIColorTriplet& bgColor = COLOR_LIST);
    void removeEntry(const char* name);
    void setBackgroundColor(const UIColor& color);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
    void setBounds(float positionX, float positionY, float width, float height) override;
    void setRadii(float radii, bool upperLeft = true, bool lowerLeft = true, bool upperRight = true, bool lowerRight = true);
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int action) override;
    inline void setCallback(ListCallback callback){ this->callback = std::move(callback); }
    void updateMesh() override;
    ~UIList();
    UIImage background;
    std::vector<UIListButton> entries;
    std::vector<Vec2i> entryValues;
    Font* font;
    int fontSize = 10;
    float entryHeight = 30.0f;
    bool autoHeight = false;
    float radii;
    bool upperLeft, lowerLeft, upperRight, lowerRight;
    ListCallback callback;
};