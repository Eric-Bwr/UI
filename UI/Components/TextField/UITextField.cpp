#include "UITextField.h"
#include "../Text/Structure/FontType.h"

UITextField::UITextField(const char *defaultText, Font *font, float width, float height, float offset)
        : UITextField(defaultText, font, height, 0, 0, width, height, offset) {}

UITextField::UITextField(const char *defaultText, float positionX, float positionY, float width, float height, float offset)
        : UITextField(defaultText, DataManager::defaultFont, height, positionX, positionY, width, height, offset) {}

UITextField::UITextField(const char *defaultText, Font *font, int fontSize, float positionX, float positionY, float width, float height, float offset)
        : text(defaultText, font, height - DataManager::getFontType(font, fontSize)->getOffset(), positionX + offset, positionY, width, height, UITextMode::CENTERED_VERTICAL_LEFT) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->defaultText = defaultText;
    this->content = defaultText;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor.standard = COLOR_RED;
    this->bgColor.hover = COLOR_RED.darker();
    this->bgColor.pressed = COLOR_RED.darker().darker();
    this->fgColor = this->cursorColor = COLOR_WHITE;
    this->fontType = DataManager::getFontType(&text);
    this->maxCharacter = INT_MAX;
    this->offset = offset;
    mesh.load(positionX, positionY, width, height, 0);
    cursorMesh.load(positionX + offset + fontType->getTextWidth(cursorContent.c_str()), positionY + cursorPadding, cursorWidth, height - cursorPadding * 2, 0);
    updateCursor();
}

void UITextField::setBackgroundColor(const UIColor &standardColor, const UIColor &hoverColor, const UIColor &pressedColor) {
    this->bgColor.standard = standardColor;
    this->bgColor.hover = hoverColor;
    this->bgColor.pressed = pressedColor;
    if (mode == 0)
        mode = 1;
    else if (mode == 2)
        mode = 3;
    mesh.loadPosition(positionX, positionY, width, height, mode);
}

void UITextField::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    if (mode == 0)
        mode = 2;
    else if (mode == 1)
        mode = 3;
    mesh.load(positionX, positionY, width, height, mode, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, hoverX, hoverY, hoverWidth, hoverHeight, pressedX, pressedY, pressedWidth, pressedHeight);
}

void UITextField::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX + offset, positionY);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextField::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextField::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x + offset, y, w, h);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextField::setFont(Font *font) {
    text.setFont(font);
    fontType = DataManager::getFontType(&text);
    updateCursor();
}

void UITextField::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
    fontType = DataManager::getFontType(&text);
    updateCursor();
}

void UITextField::setMaxCharacter(int maxCharacter) {
    this->maxCharacter = maxCharacter;
}

void UITextField::setCursorPadding(float cursorPadding) {
    this->cursorPadding = cursorPadding;
    updateCursor();
}

void UITextField::setOffset(float offset) {
    this->offset = offset;
    updateCursor();
}

void UITextField::keyInput(int key, int action, int mods) {
    if (pressed) {
        if (action == INPUT_PRESSED || action == INPUT_REPEATED) {
            if (key == KEY_BACKSPACE) {
                if (mods == KEY_MOD_CONTROL) {
                    content = content.substr(cursorContent.size(), content.size());
                    if (isPasswordField)
                        passwordContent = passwordContent.substr(cursorContent.size(), passwordContent.size());
                    cursorContent.clear();
                    text.setText(content.c_str());
                    updateCursor();
                } else {
                    if (!cursorContent.empty()) {
                        char *end = content.substr(cursorContent.size(), content.size()).data();
                        if (isPasswordField) {
                            char *passwordEnd = passwordContent.substr(cursorContent.size(), passwordContent.size()).data();
                            passwordContent = passwordContent.substr(0, cursorContent.size() - 1) + passwordEnd;
                        }
                        content = content.substr(0, cursorContent.size() - 1) + end;
                        text.setText(content.c_str());
                        cursorContent.pop_back();
                        updateCursor();
                    }
                }
            } else if (key == KEY_DELETE) {
                if (mods == KEY_MOD_CONTROL) {
                    content = content.substr(0, cursorContent.size());
                    if (isPasswordField)
                        passwordContent = passwordContent.substr(0, cursorContent.size());
                    text.setText(content.c_str());
                    updateCursor();
                } else {
                    if (cursorContent.size() < content.size()) {
                        char *start = content.substr(0, cursorContent.size()).data();
                        if (isPasswordField) {
                            char *passwordStart = passwordContent.substr(0, cursorContent.size()).data();
                            passwordContent = passwordStart + passwordContent.substr(cursorContent.size() + 1, passwordContent.size());
                        }
                        content = start + content.substr(cursorContent.size() + 1, content.size());
                        text.setText(content.c_str());
                        updateCursor();
                    }
                }
            } else if (key == KEY_LEFT) {
                if (!cursorContent.empty()) {
                    if (mods == KEY_MOD_CONTROL)
                        cursorContent.clear();
                    else
                        cursorContent.pop_back();
                    updateCursor();
                }
            } else if (key == KEY_RIGHT) {
                if (cursorContent.size() < content.size()) {
                    if (mods == KEY_MOD_CONTROL)
                        cursorContent = content;
                    else
                        cursorContent += content.substr(cursorContent.size(), 1);
                    updateCursor();
                }
            }
            if (contentCallback != nullptr)
                (*contentCallback)(content, passwordContent);
        }
    }
}

void UITextField::charInput(unsigned int key) {
    if (pressed) {
        if (content.size() < maxCharacter) {
            if (fontType->getTextWidth((content + char(key)).c_str()) < width - offset * 2 - cursorWidth) {
                char *end = content.substr(cursorContent.size(), content.size()).data();
                if (isPasswordField) {
                    char *passwordEnd = content.substr(cursorContent.size(), content.size()).data();
                    cursorContent += PASSWORD_CHARACTER;
                    passwordContent += char(key);
                    content = content.substr(0, cursorContent.size() - 1) + PASSWORD_CHARACTER + end;
                    passwordContent = passwordContent.substr(0, cursorContent.size() - 1) + char(key) + passwordEnd;
                } else {
                    cursorContent += char(key);
                    content = content.substr(0, cursorContent.size() - 1) + char(key) + end;
                }
                text.setText(content.c_str());
                updateCursor();
                if (contentCallback != nullptr)
                    (*contentCallback)(content, passwordContent);
            }
        }
    }
}

void UITextField::mousePositionInput(double x, double y) {
    bool previous = hovered;
    hovered = COMPONENT_HOVERED(x, y);
    if (hovered)
        this->mouseAdvance = x - positionX - offset;
    if (previous && !hovered || !previous && hovered)
        if (callback != nullptr)
            (*callback)(pressed, hovered);
}

#include "iostream"

void UITextField::mouseButtonInput(int button, int action) {
    bool previous = pressed;
    if (button == MOUSE_BUTTON_PRESSED && action == INPUT_PRESSED) {
        if (hovered) {
            pressed = true;
            if (content == defaultText) {
                content.clear();
                passwordContent.clear();
                text.setText(content.c_str());
            } else {
                float textAdvance = 0;
                int i;
                for (i = 0; i < content.size(); i++) {
                    if (textAdvance >= mouseAdvance)
                        break;
                    textAdvance += fontType->getCharacterWidth(content.at(i));
                }
                if (i < content.size()) {
                    float w = fontType->getCharacterWidth(content.at(i)) / 2;
                    if (textAdvance - w > mouseAdvance)
                        i--;
                } else {
                    float w = fontType->getCharacterWidth(content.back()) / 2;
                    if (textAdvance - w > mouseAdvance)
                        i--;
                }
                cursorContent = content.substr(0, i);
                updateCursor();
            }
        } else {
            pressed = false;
            if (content.empty()) {
                content = defaultText;
                cursorContent.clear();
                passwordContent.clear();
                text.setText(content.c_str());
            }
        }
    }
    if (callback != nullptr)
        if (previous && !pressed || !previous && pressed)
            (*callback)(pressed, hovered);
}

void UITextField::updateCursor() {
    cursorMesh.loadPosition(positionX + offset + fontType->getTextWidth(cursorContent.c_str()) - cursorWidth / 2, positionY + cursorPadding, cursorWidth, height - cursorPadding * 2);
}