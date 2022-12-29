#pragma once

#include <OpenGL/Texture.h>
#include <functional>
#include <utility>
#include "../UIComponent.h"
#include "../../UIStructure/QuadMesh.h"
#include "../../UIColor.h"
#include "../Text/UIText.h"

class UITextField : public UIComponent {
public:
    void init(char* defaultText, Font* font = DataManager::defaultFont, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);
    void init(char* defaultText, float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);
    void init(char* defaultText, Font* font, int fontSize, float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);

    void setBackgroundColor(const UIColor& standardColor, const UIColor& hoverColor, const UIColor& pressedColor);
    void setBackgroundTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight);
    void setBackgroundTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
	void setBounds(float positionX, float positionY, float width, float height) override;
	void setText(const char* text);
    void setFont(Font *font);
	void setFontSize(int fontSize);
	void setMaxCharacter(int maxCharacter);
	void setCursorPadding(float cursorPadding);
	void setOffset(float offset);
    void setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight);
	void setPasswordVisible(bool visible);
	inline void setPasswordField(bool isPasswordField){ this->isPasswordField = isPasswordField; }
	inline void setOnlyNumbers(bool onlyNumbers){ this->onlyNumbers = onlyNumbers; }
    inline void setButtonCallback(ButtonCallback buttonCallback){ this->callback = std::move(buttonCallback); }
    inline void setContentCallback(DContentCallback contentCallback){ this->contentCallback = std::move(contentCallback); }

    inline std::string getContent() const { return content; }
	inline std::string getPasswordContent() const { return passwordContent; }

    void keyInput(int key, int action, int mods) override;
    void charInput(unsigned int key) override;
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int action) override;
    void updateMesh() override;

    bool hovered = false, pressed = false;
    float cursorWidth = CURSOR_WIDTH, cursorPadding = CURSOR_PADDING, offset = 0;
    const char* defaultText;
    std::string content, cursorContent, passwordContent;
    QuadMeshTriplet mesh;
    QuadMesh cursorMesh;
    Texture* texture;
    UIColorTriplet bgColor;
    UIColor fgColor;
    UIColor cursorColor;
    UIText text;
    int maxCharacter, mode = 0;
    bool isPasswordField = false, onlyNumbers = false;
    double mouseAdvance = 0;
    void updateCursor();
    DContentCallback contentCallback;
    ButtonCallback callback;
};