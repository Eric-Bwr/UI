#include "UITextField.h"
#include "../Text/Structure/FontType.h"

UITextField::UITextField(const char *defaultText, float width, float height)
        : text(defaultText, height, positionX, positionY, width, height, UITextMode::CENTERED_VERTICAL_LEFT) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->defaultText = defaultText;
    this->content = defaultText;
    this->positionX = 0;
    this->positionY = 0;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_WHITE;
    this->fgColor = COLOR_RED;
    this->cursorColor = COLOR_BLACK;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    this->fontType = DataManager::getFontType(&text);
    mesh.load(positionX, positionY, width, height, 0);
    updateCursor();
}

UITextField::UITextField(const char *defaultText, float positionX, float positionY, float width, float height)
        : text(defaultText, 110, positionX, positionY, width, height, UITextMode::CENTERED_VERTICAL_LEFT) {
    type = UIComponentType::UITEXTFIELD;
    texture = nullptr;
    this->defaultText = defaultText;
    this->content = defaultText;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor = COLOR_WHITE;
    this->fgColor = COLOR_RED;
    this->cursorColor = COLOR_BLACK;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    this->fontType = DataManager::getFontType(&text);
    mesh.load(positionX, positionY, width, height, 0);
    updateCursor();
}

void UITextField::setTexture(Texture *texture) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UITextField::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX, positionY);
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    updateCursor();
}

void UITextField::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    updateCursor();
}

void UITextField::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x, y, w, h);
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    updateCursor();
}

/*
void UITextField::setText(const char *string, Font *font, int fontSize) {
    text.text = string;
    text.font = font;
    text.positionX = positionX;
    text.positionY = positionY;
    text.setFontSize(fontSize);
}

void UITextField::setText(const char *string) {
    text.setText(string);
}

void UITextField::setFont(Font *font) {
    text.setFont(font);
}

void UITextField::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
}
*/

void UITextField::keyInput(int key, int action, int mods) {
    if (pressed) {
        if (action == INPUT_PRESSED || action == INPUT_REPEATED) {
            if (key == KEY_BACKSPACE) {
                if (mods == KEY_MOD_CONTROL) {
                    content = content.substr(cursorContent.size(), content.size());
                    cursorContent.clear();
                    text.setText(content.c_str());
                    updateCursor();
                } else {
                    if (!cursorContent.empty()) {
                        char *end = content.substr(cursorContent.size(), content.size()).data();
                        content = content.substr(0, cursorContent.size() - 1) + end;
                        text.setText(content.c_str());
                        cursorContent.pop_back();
                        updateCursor();
                    }
                }
            } else if (key == KEY_DELETE) {
                if (mods == KEY_MOD_CONTROL) {
                    content = content.substr(0, cursorContent.size());
                    text.setText(content.c_str());
                    updateCursor();
                } else {
                    if (cursorContent.size() < content.size()) {
                        char *start = content.substr(0, cursorContent.size()).data();
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
        }
    }
}

void UITextField::charInput(unsigned int key) {
    if (pressed) {
        if(fontType->getTextWidth((content + char(key)).c_str()) < width) {
            char *end = content.substr(cursorContent.size(), content.size()).data();
            cursorContent += char(key);
            content = content.substr(0, cursorContent.size() - 1) + char(key) + end;
            text.setText(content.c_str());
            updateCursor();
        }
    }
}

void UITextField::mousePositionInput(double x, double y) {
    hovered = COMPONENT_HOVERED(x, y);
}

void UITextField::mouseButtonInput(int button, int action) {
    if (button == MOUSE_BUTTON_PRESSED && action == INPUT_PRESSED) {
        if (hovered) {
            pressed = true;
            if (content == defaultText) {
                content.clear();
                text.setText(content.c_str());
            }
        } else {
            pressed = false;
            if (content.empty()) {
                content = defaultText;
                cursorContent.clear();
                text.setText(content.c_str());
            }
        }
    }
}

void UITextField::updateCursor() {
    cursorMesh.load(positionX + fontType->getTextWidth(cursorContent.c_str()), positionY, cursorWidth, height, 0);
}