#pragma once

#include <string>
#include <Math/Vector.h>

#define COLOR_DECIMAL 1
#define COLOR_NORMALIZED 2

class UIColor{
public:
    UIColor();
    UIColor(float red, float green, float blue, float alpha, int colorMode);
    explicit UIColor(const char* hex, float alpha = 1.0f);
    Vec4f getNormalizedDecimal() const;
    Vec4f getDecimal() const;
    std::string getHex();
    void setRGBA(float red, float green, float blue, float alpha, int colorMode);
    void setRed(float red,int colorMode);
    void setGreen(float green,int colorMode);
    void setBlue(float blue,int colorMode);
    void setAlpha(float alpha,int colorMode);
    ~UIColor();
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
};