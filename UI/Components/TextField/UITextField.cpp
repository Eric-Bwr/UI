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
    this->bgColor = COLOR_WHITE;
    this->fgColor = COLOR_RED;
    this->cursorColor = COLOR_BLACK;
    this->hoveredColor = bgColor.darker();
    this->pressedColor = bgColor.darker().darker();
    this->fontType = DataManager::getFontType(&text);
    this->maxCharacter = INT_MAX;
    this->offset = offset;
    mesh.load(positionX, positionY, width, height, 0);
    hoverMesh.load(positionX, positionY, width, height, 0);
    pressedMesh.load(positionX, positionY, width, height, 0);
    cursorMesh.load(positionX + offset + fontType->getTextWidth(cursorContent.c_str()), positionY + cursorPadding, cursorWidth, height - cursorPadding * 2, 0);
    updateCursor();
}

void UITextField::setTexture(Texture *texture) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, texture != nullptr);
    hoverMesh.load(positionX, positionY, width, height, texture != nullptr);
    pressedMesh.load(positionX, positionY, width, height, texture != nullptr);
}

void UITextField::setTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    mesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, texture != nullptr);
    hoverMesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), hoverX, hoverY, hoverWidth, hoverHeight, texture != nullptr);
    pressedMesh.load(positionX, positionY, width, height, texture->getWidth(), texture->getHeight(), pressedX, pressedY, pressedWidth, pressedHeight, texture != nullptr);
}

void UITextField::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX + offset, positionY);
    mesh.loadPosition(positionX, positionY, width, height);
    hoverMesh.loadPosition(positionX, positionY, width, height);
    pressedMesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextField::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.loadPosition(positionX, positionY, width, height);
    hoverMesh.loadPosition(positionX, positionY, width, height);
    pressedMesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextField::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x + offset, y, w, h);
    mesh.loadPosition(positionX, positionY, width, height);
    hoverMesh.loadPosition(positionX, positionY, width, height);
    pressedMesh.loadPosition(positionX, positionY, width, height);
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
        if (content.size() < maxCharacter) {
            if (fontType->getTextWidth((content + char(key)).c_str()) < width - offset - cursorWidth) {
                char *end = content.substr(cursorContent.size(), content.size()).data();
                cursorContent += char(key);
                content = content.substr(0, cursorContent.size() - 1) + char(key) + end;
                text.setText(content.c_str());
                updateCursor();
            }
        }
    }
}

void UITextField::mousePositionInput(double x, double y) {
    hovered = COMPONENT_HOVERED(x, y);
    if (hovered)
        this->mouseAdvance = x - positionX - offset;
}

void UITextField::mouseButtonInput(int button, int action) {
    if (button == MOUSE_BUTTON_PRESSED && action == INPUT_PRESSED) {
        if (hovered) {
            pressed = true;
            if (content == defaultText) {
                content.clear();
                text.setText(content.c_str());
            } else {
                float textAdvance = 0;
                int i;
                for (i = 0; i < content.size(); i++) {
                    if (textAdvance > mouseAdvance)
                        break;
                    textAdvance += fontType->getCharacterWidth(content.at(i));
                }
                if (content.size() > i) {
                    float w = fontType->getCharacterWidth(content.at(i)) / 2;
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
                text.setText(content.c_str());
            }
        }
    }
}

void UITextField::updateCursor() {
    cursorMesh.loadPosition(positionX + offset + fontType->getTextWidth(cursorContent.c_str()), positionY + cursorPadding, cursorWidth, height - cursorPadding * 2);
}