#include "UITextArea.h"
#include "../Text/Structure/FontType.h"

UITextArea::UITextArea(float positionX, float positionY, float width, float height, float offset)
        : UITextArea(DataManager::defaultFont, 20, positionX, positionY, width, height, offset) {}

UITextArea::UITextArea(Font *font, int fontSize, float positionX, float positionY, float width, float height, float offset, int mode)
        : text("", font, fontSize, positionX + offset, positionY + offset, width - offset * 2 - cursorWidth, height, mode) {
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
    this->offset = offset;
    this->fieldWidth = width - offset * 2 - cursorWidth;
    mesh.load(positionX, positionY, width, height, 0);
    cursorMesh.load(positionX + offset + text.fontType->getTextWidth(cursorContent.data()), positionY + cursorPadding, cursorWidth, height - cursorPadding * 2, 0);
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
    this->fieldWidth = width - offset * 2 - cursorWidth;
    text.setSize(fieldWidth, height);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

void UITextArea::setBounds(float positionX, float positionY, float width, float height) {
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
    this->fieldWidth = width - offset * 2 - cursorWidth;
    text.setBounds(positionX + offset, positionY, fieldWidth, height);
    mesh.loadPosition(positionX, positionY, width, height);
    updateCursor();
}

#include "iostream"

void UITextArea::setText(char *string) {
    text.text = string;
    text.textMesh.loadTextStructure();
    text.textMesh.loadText();
    currentLine = text.textMesh.lines.size() - 1;
    updateUntilLine();
    updateLine();
    cursorContent = currentLineContent;
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

void UITextArea::setCursorPadding(float cursorPadding) {
    this->cursorPadding = cursorPadding;
    updateCursor();
}

void UITextArea::setOffset(float offset) {
    this->offset = offset;
    this->fieldWidth = width - offset * 2 - cursorWidth;
    text.setBounds(positionX + offset, positionY, fieldWidth, height);
    updateCursor();
}

void UITextArea::setRadii(float radii, bool upperLeft, bool lowerLeft, bool upperRight, bool lowerRight) {
    mesh.setRadii(radii, upperLeft, lowerLeft, upperRight, lowerRight);
}

static bool shouldStop(char input){
    return input == ' ' || input == '.' || input == ',' || input == ':' || input == ';' || input == '!' || input == '?' || input == '-' || input == '_' || input == '+' || input == '#' || input == '~' || input == '*' || input == '/' || input == '\n' || input == '\r';
}

void UITextArea::keyInput(int key, int action, int mods) {
    if (pressed) {
        if (action == INPUT_PRESSED || action == INPUT_REPEATED) {
            updateUntilLine();
            if (key == KEY_TAB)
                charInput(char('\t'));
            else if (key == KEY_BACKSPACE) {
                if (cursorContent.empty() && currentLine > 0) {
                    currentLine--;
                    updateLine();
                    updateUntilLine();
                    cursorContent = currentLineContent;
                } else if (cursorContent.empty() && currentLine == 0)
                    return;
                if (mods == KEY_MOD_CONTROL) {
                    int dstToLastSpace;
                    for (dstToLastSpace = cursorContent.size() - 1; dstToLastSpace > 0; dstToLastSpace--) {
                        if (shouldStop(cursorContent.at(dstToLastSpace)))
                            break;
                    }
                    if (text.text.size() > 1)
                        text.text = text.text.substr(0, currentContentUntilLine.size() + dstToLastSpace) +
                                    text.text.substr(currentContentUntilLine.size() + cursorContent.size(),
                                                     text.text.size());
                    else
                        text.text = text.text.substr(0, currentContentUntilLine.size() + dstToLastSpace);
                    cursorContent = cursorContent.substr(0, dstToLastSpace);
                    text.textMesh.loadTextStructure();
                    text.textMesh.loadText();
                } else {
                    cursorContent.pop_back();
                    updateUntilLine();
                    if (text.text.size() > 1)
                        text.text = text.text.substr(0, currentContentUntilLine.size() + cursorContent.size()) +
                                    text.text.substr(currentContentUntilLine.size() + cursorContent.size() + 1,
                                                     text.text.size());
                    else
                        text.text = text.text.substr(0, currentContentUntilLine.size() + cursorContent.size());
                    text.textMesh.loadTextStructure();
                    text.textMesh.loadText();
                }
            } else if (key == KEY_DELETE) {
                if (mods == KEY_MOD_CONTROL) {
                    int dstToNextSpace;
                    for (dstToNextSpace = cursorContent.size();
                        dstToNextSpace < currentLineContent.size(); dstToNextSpace++) {
                        if(shouldStop(currentLineContent.at(dstToNextSpace)))
                            break;
                    }
                    dstToNextSpace -= cursorContent.size();
                    std::cout << dstToNextSpace << " <<\n";
                    //text.text = text.text.substr(0, currentContentUntilLine.size() + cursorContent.size()) +
                    //            text.text.substr(currentContentUntilLine.size() + cursorContent.size() + dstToNextSpace,
                    //                             text.text.size());
                    text.textMesh.loadTextStructure();
                    text.textMesh.loadText();
                } else {
                    if (cursorContent.size() < currentLineContent.size() - 1) {
                        auto start = text.text.substr(0, currentContentUntilLine.size() + cursorContent.size() + 1);
                        text.text = start + text.text.substr(currentContentUntilLine.size() + cursorContent.size() + 2,
                                                             text.text.size());
                        updateLine();
                        text.textMesh.loadTextStructure();
                        text.textMesh.loadText();
                    }
                }
                updateUntilLine();
            } else if (key == KEY_LEFT) {
                if (!cursorContent.empty()) {
                    if (mods == KEY_MOD_CONTROL)
                        cursorContent.clear();
                    else
                        cursorContent.pop_back();
                }
            } else if (key == KEY_RIGHT) {
                if (cursorContent.size() < currentLineContent.size()) {
                    if (mods == KEY_MOD_CONTROL)
                        if (currentLineContent.back() == ' ')
                            cursorContent = currentLineContent.substr(0, currentLineContent.size() - 1);
                        else
                            cursorContent = currentLineContent;
                    else if (!(cursorContent.size() == currentLineContent.size() - 1 &&
                               currentLineContent.back() == ' '))
                        cursorContent += currentLineContent.substr(cursorContent.size(), 1);
                }
            } else if (key == KEY_UP) {
                if (currentLine > 0) {
                    float previousLength = text.fontType->getTextWidth(cursorContent.data());
                    currentLine--;
                    updateUntilLine();
                    updateLine();
                    float textAdvance = 0;
                    int i;
                    for (i = 0; i < currentLineContent.size(); i++) {
                        if (textAdvance >= previousLength || (currentLineContent.at(i) == ' ' && i == currentLineContent.size() - 1))
                            break;
                        textAdvance += text.fontType->getCharacterWidth(currentLineContent.at(i));
                    }
                    if (i < currentLineContent.size()) {
                        float w = text.fontType->getCharacterWidth(currentLineContent.at(i)) / 2;
                        if (textAdvance - w > previousLength)
                            i--;
                    } else {
                        float w = text.fontType->getCharacterWidth(currentLineContent.back()) / 2;
                        if (textAdvance - w > previousLength)
                            i--;
                    }
                    cursorContent = currentLineContent.substr(0, i);
                }
            } else if (key == KEY_DOWN) {
                if (currentLine < text.textMesh.lines.size() - 1) {
                    float previousLength = text.fontType->getTextWidth(cursorContent.data());
                    currentLine++;
                    updateUntilLine();
                    updateLine();
                    float textAdvance = 0;
                    int i;
                    for (i = 0; i < currentLineContent.size(); i++) {
                        if (textAdvance >= previousLength)
                            break;
                        textAdvance += text.fontType->getCharacterWidth(currentLineContent.at(i));
                    }
                    if (i < currentLineContent.size()) {
                        float w = text.fontType->getCharacterWidth(currentLineContent.at(i)) / 2;
                        if (textAdvance - w > previousLength)
                            i--;
                    } else {
                        float w = text.fontType->getCharacterWidth(currentLineContent.back()) / 2;
                        if (textAdvance - w > previousLength)
                            i--;
                    }
                    cursorContent = currentLineContent.substr(0, i);
                }
            }
            //if (contentCallback != nullptr)
            //    (*contentCallback)(content);
        }
        updateCursor();
    }
}

void UITextArea::updateUntilLine() {
    currentContentUntilLine.clear();
    for (int i = 0; i < currentLine; i++) {
        for (const auto &word : text.textMesh.lines.at(i).words) {
            if (word.characters.empty())
                currentContentUntilLine += " ";
            else
                for (auto character : word.characters)
                    currentContentUntilLine += character;
        }
    }
}

void UITextArea::updateLine() {
    currentLineContent.clear();
    for (const auto &word : text.textMesh.lines.at(currentLine).words) {
        if (word.characters.empty())
            currentLineContent += " ";
        else
            for (auto character : word.characters)
                currentLineContent += character;
    }
}

void UITextArea::charInput(unsigned int key) {
    updateUntilLine();
    updateLine();
    if (pressed) {
        if(cursorContent.back() == '\n')
            cursorContent.pop_back();
        auto end = text.text.substr(currentContentUntilLine.size() + cursorContent.size(), text.text.size());
        text.text = text.text.substr(0, currentContentUntilLine.size() + cursorContent.size()) + char(key) + end;
        int dstToNextSpace;
        for (dstToNextSpace = cursorContent.size(); dstToNextSpace < currentLineContent.size(); dstToNextSpace++) {
            if (shouldStop(currentLineContent.at(dstToNextSpace)))
                break;
        }
        dstToNextSpace -= cursorContent.size();
        auto part = currentLineContent.substr(cursorContent.size(), dstToNextSpace);
        //FIXME: If a word is above the size of the textFieldWidth we got a lil bit of an oopsie
        if (text.fontType->getTextWidth((cursorContent + char(key) + part).data()) > fieldWidth) {
            int dstToLastSpace;
            for (dstToLastSpace = cursorContent.size() - 1; dstToLastSpace > 0; dstToLastSpace--) {
                if (shouldStop(cursorContent.at(dstToLastSpace)))
                    break;
            }
            cursorContent = cursorContent.substr(dstToLastSpace, cursorContent.size()) + char(key);
            if (cursorContent.front() == ' ')
                cursorContent = cursorContent.substr(1, cursorContent.size());
            currentLine++;
            updateUntilLine();
        } else
            cursorContent += char(key);
        text.textMesh.loadTextStructure();
        updateLine();
        updateCursor();
        text.textMesh.loadText();
        //if (contentCallback != nullptr)
        //    (*contentCallback)(content);
    }
}

void UITextArea::mousePositionInput(double x, double y) {
    bool previous = hovered;
    hovered = COMPONENT_HOVERED(x, y);
    if (hovered) {
        this->mouseAdvanceX = x - positionX - offset;
        this->mouseAdvanceY = y - positionY - offset;
    }
    if (previous && !hovered || !previous && hovered)
        if (callback != nullptr)
            (*callback)(pressed, hovered);
}

void UITextArea::mouseButtonInput(int action) {
    bool previous = pressed;
    if (action == INPUT_PRESSED) {
        if (hovered) {
            pressed = true;
            if (!text.text.empty()) {
                currentLine = 0;
                for (currentLine = 0; currentLine < text.textMesh.lines.size(); currentLine++) {
                    if (currentLine * text.fontSize > mouseAdvanceY)
                        break;
                }
                currentLine--;
                updateLine();
                float textAdvance = 0;
                int i;
                for (i = 0; i < currentLineContent.size(); i++) {
                    if (textAdvance >= mouseAdvanceX)
                        break;
                    textAdvance += text.fontType->getCharacterWidth(currentLineContent.at(i));
                }
                if (i < currentLineContent.size()) {
                    float w = text.fontType->getCharacterWidth(currentLineContent.at(i)) / 2;
                    if (textAdvance - w > mouseAdvanceX)
                        i--;
                } else {
                    float w = text.fontType->getCharacterWidth(currentLineContent.back()) / 2;
                    if (textAdvance - w > mouseAdvanceX)
                        i--;
                }
                cursorContent = currentLineContent.substr(0, i);
                updateCursor();
            }
        } else
            pressed = false;
    }
    if (callback != nullptr)
        if (previous && !pressed || !previous && pressed)
            (*callback)(pressed, hovered);
}

void UITextArea::updateCursor() {
    cursorMesh.loadPosition(positionX + offset + text.fontType->getTextWidth(cursorContent.data()) - cursorWidth / 2, positionY + cursorPadding + text.fontSize * currentLine, cursorWidth, text.fontSize - cursorPadding * 2);
}