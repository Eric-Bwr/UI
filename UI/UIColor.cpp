#include "UIColor.h"

#include <sstream>

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

UIColor::UIColor(int hex, float alpha) {
    a = alpha;
	r = ((hex >> 16) & 0xFF) / 255.0;
	g = ((hex >> 8) & 0xFF) / 255.0;
	b = ((hex) & 0xFF) / 255.0;
}

UIColor::UIColor(const std::string& hex, float alpha) {
	a = alpha;
	int rgb;
	if (hex[0] == '#')
		rgb = std::stoi(hex.substr(1), nullptr, 16);
	else
		rgb = std::stoi(hex, nullptr, 16);
	r = ((rgb >> 16) & 0xFF) / 255.0;
	g = ((rgb >> 8) & 0xFF) / 255.0;
	b = ((rgb) & 0xFF) / 255.0;
}

Vec4f UIColor::getNormalizedDecimal() const{
    return {r, g, b, a};
}

Vec4f UIColor::getDecimal() const {
    return {r * 255.0f, g * 255.0f, b * 255.0f, a * 255.0f};
}

std::string UIColor::getHexString(bool alpha, std::string heading) {
	int hex = getHex(alpha);
	std::stringstream ss;
	ss << heading << std::hex << hex;
	return ss.str();
}

int UIColor::getHex(bool alpha) {
	int rr = (int)(r * 255);
	int gg = (int)(g * 255);
	int bb = (int)(b * 255);
	int aa = (int)(a * 255);

	if (alpha)
		return aa << 24 | rr << 16 | gg << 8 | bb;

	return rr << 16 | gg << 8 | bb;
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