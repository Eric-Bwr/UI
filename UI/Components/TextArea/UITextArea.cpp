#include "UITextArea.h"
#include "../Text/Structure/FontType.h"

UITextArea::UITextArea(float positionX, float positionY, float width, float height, float offset)
        : UITextArea(DataManager::defaultFont, 20, positionX, positionY, width, height, offset) {}

UITextArea::UITextArea(Font *font, int fontSize, float positionX, float positionY, float width, float height, float offset, int mode)
        : text("", font, fontSize, positionX + offset, positionY, width - offset * 2, height, mode) {
    type = UIComponentType::UITEXTAREA;
    texture = nullptr;
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->bgColor.standard = COLOR_RED;
    this->bgColor.hover = COLOR_RED.darker();
    this->bgColor.pressed = COLOR_RED.darker().darker();
    this->fgColor = this->cursorColor = COLOR_WHITE;
    this->maxCharacter = INT_MAX;
    this->offset = offset;
    mesh.load(positionX, positionY, width, height, 0);
    cursorMesh.load(positionX + offset + text.fontType->getTextWidth(cursorContent.c_str()), positionY + cursorPadding, cursorWidth, height - cursorPadding * 2, 0);
    updateCursor();
}

void UITextArea::setBackgroundColor(const UIColor &standardColor, const UIColor &hoverColor, const UIColor &pressedColor) {
    this->bgColor.standard = standardColor;
    this->bgColor.hover = hoverColor;
    this->bgColor.pressed = pressedColor;
    if (mode == 0)
        mode = 1;
    else if (mode == 2)
        mode = 3;
    mesh.loadPosition(positionX, positionY, width, height, mode);
}

void UITextArea::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
    this->texture = texture;
    if (mode == 0)
        mode = 2;
    else if (mode == 1)
        mode = 3;
    mesh.load(positionX, positionY, width, height, mode, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, buttonX, buttonY, buttonWidth, buttonHeight, buttonX, buttonY, buttonWidth, buttonHeight);
}

void UITextArea::setBackgroundTexture(Texture *texture, float buttonX, float buttonY, float buttonWidth, float buttonHeight, float hoverX, float hoverY, float hoverWidth, float hoverHeight, float pressedX, float pressedY, float pressedWidth, float pressedHeight) {
    this->texture = texture;
    if (mode == 0)
        mode = 2;
    else if (mode == 1)
        mode = 3;
    mesh.load(positionX, positionY, width, height, mode, texture->getWidth(), texture->getHeight(), buttonX, buttonY, buttonWidth, buttonHeight, hoverX, hoverY, hoverWidth, hoverHeight, pressedX, pressedY, pressedWidth, pressedHeight);
}

void UITextArea::setPosition(float positionX, float positionY) {
    this->positionX = positionX;
    this->positionY = positionY;
    text.setPosition(positionX + offset, positionY);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextArea::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    text.setSize(width, height);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextArea::setBounds(float x, float y, float w, float h) {
    this->positionX = x;
    this->positionY = y;
    this->width = w;
    this->height = h;
    text.setBounds(x + offset, y, w, h);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextArea::setText(const char *string) {
    text.text = string;
    text.textMesh.loadTextStructure();
    text.textMesh.loadText();
    lineToString(text.textMesh.lines.size() - 1);
    cursorContent = currentLineContent;
    currentLINE
    updateCursor();
}

void UITextArea::setFont(Font *font) {
    text.setFont(font);
    updateCursor();
}

void UITextArea::setFontSize(int fontSize) {
    text.setFontSize(fontSize);
    updateCursor();
}

void UITextArea::setMaxCharacter(int maxCharacter) {
    this->maxCharacter = maxCharacter;
}

void UITextArea::setCursorPadding(float cursorPadding) {
    this->cursorPadding = cursorPadding;
    updateCursor();
}

void UITextArea::setOffset(float offset) {
    this->offset = offset;
    updateCursor();
}

void UITextArea::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    mesh.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
}

/*
void UITextArea::keyInput(int key, int action, int mods) {
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
            if (contentCallback != nullptr)
                (*contentCallback)(content);
        }
    }
}
*/

void UITextArea::lineToString(int line){
    currentLineContent.clear();
    for(auto words : text.textMesh.lines.at(line).words){
        currentLineContent += words.characters.data();
    }
}

void UITextArea::charInput(unsigned int key) {
    if (pressed) {
        /*if (lines[currentLine].size() < maxCharacter) {
            if (fontType->getTextWidth((lines[currentLine] + char(key)).c_str()) < width - offset * 2 - cursorWidth) {
                char *end = lines[currentLine].substr(cursorContent.size(), lines[currentLine].size()).data();
                cursorContent += char(key);
                lines[currentLine] = lines[currentLine].substr(0, cursorContent.size() - 1) + char(key) + end;
                updateText();
                //if (contentCallback != nullptr)
                //    (*contentCallback)(content);
            }else{
               // cursorContent = char(key);
               // content += "\n";
               // content += char(key);
               // text.setText(totalContent.c_str());
               // updateCursor();
                //if (contentCallback != nullptr)
                //    (*contentCallback)(content);
            }
        }
         */
    }
}

void UITextArea::mousePositionInput(double x, double y) {
    bool previous = hovered;
    hovered = COMPONENT_HOVERED(x, y);
    if (hovered)
        this->mouseAdvance = x - positionX - offset;
    if (previous && !hovered || !previous && hovered)
        if (callback != nullptr)
            (*callback)(pressed, hovered);
}

void UITextArea::mouseButtonInput(int action) {
    bool previous = pressed;
    if (action == INPUT_PRESSED) {
        if (hovered) {
            pressed = true;
            /*if (!content.empty()) {
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
                */

        } else
            pressed = false;
    }
    if (callback != nullptr)
        if (previous && !pressed || !previous && pressed)
            (*callback)(pressed, hovered);
}

void UITextArea::updateCursor() {
    cursorMesh.loadPosition(positionX + offset + text.fontType->getTextWidth(cursorContent.c_str()) - cursorWidth / 2, positionY + cursorPadding + text.fontType->height * currentLine, cursorWidth, text.fontType->height - cursorPadding * 2);
}