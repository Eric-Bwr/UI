#include "UIColor.h"

UIColor::UIColor() = default;

UIColor::UIColor(float red, float green, float blue, float alpha, int colorMode) {
    if(colorMode == COLOR_DECIMAL){
        this->r = red / 255.0f;
        this->g = green / 255.0f;
        this->b = blue / 255.0f;
        this->a = alpha / 255.0f;
    }else{
        this->r = red;
        this->g = green;
        this->b = blue;
        this->a = alpha;
    }
}

UIColor::UIColor(const char *hex, float alpha) {
    this->a = alpha;
    std::string input = hex;
    if(input.at(0) == '#')
        input.erase(0, 1);
    if(input.size() == 6){
        int hexValues[6];
        for (int i = 0; i < 6; i++){
            char letter = input.at(i);
            if(letter == 'A' || letter == 'a'){
                hexValues[i] = 10;
            }else if(letter == 'B'|| letter == 'b'){
                hexValues[i] = 11;
            }else if(letter == 'C'|| letter == 'c'){
                hexValues[i] = 12;
            }else if(letter == 'D'|| letter == 'd'){
                hexValues[i] = 13;
            }else if(letter == 'E'|| letter == 'e'){
                hexValues[i] = 14;
            }else if(letter == 'F'|| letter == 'f'){
                hexValues[i] = 15;
            }else{
                auto temp = new std::string;
                *temp += (letter);
                hexValues[i] = atoi(temp->c_str());
                delete temp;
            }
        }
        for(int i = 0; i < 6; i += 2) {
            auto value1 = (float)hexValues[i];
            auto value2 = (float)hexValues[i + 1];
            float result = ((value1 * 16.0f) + value2) / 255.0f;
            if (i == 0)
                r = result;
            else if (i == 2)
                g = result;
            else if (i == 4)
                b = result;
        }
    }
}

Vec4f UIColor::getNormalizedDecimal() const{
    return {r, g, b, a};
}

Vec4f UIColor::getDecimal() const {
    return {r * 255.0f, g * 255.0f, b * 255.0f, a * 255.0f};
}

std::string UIColor::getHex() {
    r *= 255.0f;
    g *= 255.0f;
    b *= 255.0f;
    a *= 255.0f;
    float hexValues[6];
    hexValues[0] = r / 16.0f;
    hexValues[1] = r - (hexValues[0] * 16);
    hexValues[2] = g /  16.0f;
    hexValues[3] = g - (hexValues[2] * 16);
    hexValues[4] = b /  16.0f;
    hexValues[5] = b - (hexValues[4] * 16);
    std::string result;
    result += '#';
    for(float hexValue : hexValues){
        if(hexValue == 10)
            result += 'a';
        else if(hexValue == 11)
            result += 'b';
        else if(hexValue == 12)
            result += 'c';
        else if(hexValue == 13)
            result += 'd';
        else if(hexValue == 14)
            result += 'e';
        else if(hexValue == 15)
            result += 'f';
        else
            result += std::to_string(hexValue);
    }
    r /= 255.0f;
    g /= 255.0f;
    b /= 255.0f;
    a /= 255.0f;
    return result;
}

void UIColor::setRGBA(float red, float green, float blue, float alpha, int colorMode) {
    if(colorMode == COLOR_NORMALIZED){
        this->r = red;
        this->g = green;
        this->b = blue;
        this->a = alpha;
    }else if(colorMode == COLOR_DECIMAL){
        this->r = (red / 255);
        this->g = (green / 255);
        this->b = (blue / 255);
        this->a = (alpha / 255);
    }
}

void UIColor::setRed(float red, int colorMode) {
    if(colorMode == COLOR_NORMALIZED){
        this->r = red;
    }else if(colorMode == COLOR_DECIMAL){
        this->r = (red / 255);
    }
}

void UIColor::setGreen(float green, int colorMode) {
    if(colorMode == COLOR_NORMALIZED){
        this->g = green;
    }else if(colorMode == COLOR_DECIMAL){
        this->g = (green / 255);
    }
}

void UIColor::setBlue(float blue,int colorMode) {
    if(colorMode == COLOR_NORMALIZED){
        this->b = blue;
    }else if(colorMode == COLOR_DECIMAL){
        this->b = (blue / 255);
    }
}

void UIColor::setAlpha(float alpha, int colorMode) {
    if(colorMode == COLOR_NORMALIZED){
        this->a = alpha;
    }else if(colorMode == COLOR_DECIMAL){
        this->a = (alpha / 255);
    }
}

UIColor::~UIColor() = default;