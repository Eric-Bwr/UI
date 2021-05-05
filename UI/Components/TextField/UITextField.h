#pragma once

#include <Texture.h>
#include "../UIComponent.h"
#include "../../Structure/QuadMesh.h"
#include "../../UIColor.h"
#include "../Text/UIText.h"

class UITextField : public UIComponent {
public:
    explicit UITextField(const char* defaultText, Font* font = DataManager::defaultFont, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);
    UITextField(const char* defaultText, float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);
    UITextField(const char* defaultText, Font* font, int fontSize, float positionX, float positionY, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, float offset = 0);
    void setTexture(Texture* texture);
    void setTexture(Texture* texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight);
    void setPosition(float positionX, float positionY) override;
    void setSize(float width, float height);
	void setBounds(float, float, float, float) override;
    void setFont(Font *font);
	void setFontSize(int fontSize);
	void setMaxCharacter(int maxCharacter);
	void setCursorPadding(float cursorPadding);
	void setOffset(float offset);
	inline void setPasswordField(bool isPasswordField){ this->isPasswordField = isPasswordField; }
	inline std::string getContent() const { return content; }
	inline std::string getPasswordContent() const { return passwordContent; }
    void keyInput(int key, int action, int mods) override;
    void charInput(unsigned int key) override;
    void mousePositionInput(double x, double y) override;
    void mouseButtonInput(int button, int action) override;
    inline void setCallback(void(*callback)(bool pressed, bool hovered)){ this->callback = callback; }
    bool hovered = false, pressed = false;
    float cursorWidth = CURSOR_WIDTH, cursorPadding = CURSOR_PADDING, offset = 0;
    const char* defaultText;
    std::string content, cursorContent, passwordContent;
    QuadMesh mesh;
    QuadMesh hoverMesh;
    QuadMesh pressedMesh;
    QuadMesh cursorMesh;
    Texture* texture;
    UIColor bgColor;
    UIColor fgColor;
    UIColor cursorColor;
    UIColor hoveredColor;
    UIColor pressedColor;
    UIText text;
private:
    FontType* fontType;
    int maxCharacter;
    bool isPasswordField = false;
    double mouseAdvance = 0;
    void updateCursor();
    void (*callback)(bool pressed, bool hovered) = nullptr;
};
