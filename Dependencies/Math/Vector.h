#pragma once

#include <cmath>

#ifndef RADIANS
#define RADIANS 0.01745329251994329576923690768489
#endif

template<typename T = float>
class Vec2 {
public:
    T x = 0, y = 0;

    Vec2() = default;
    explicit Vec2(T v){
        this->x = v;
        this->y = v;
    }
    Vec2(T x, T y){
        this->x = x;
        this->y = y;
    }
    Vec2(const Vec2 &v){
        this->x = v.x;
        this->y = v.y;
    }

    friend Vec2 operator+ (const Vec2 &a, const Vec2 &b){
        return Vec2<T>(a.x + b.x, a.y + b.y);
    }
    friend Vec2 operator+ (const Vec2 &a, T b){
        return Vec2<T>(a.x + b, a.y + b);
    }
    friend Vec2 operator- (const Vec2 &a, const Vec2 &b){
        return Vec2<T>(a.x - b.x, a.y - b.y);
    }
    friend Vec2 operator- (const Vec2 &a, T b){
        return Vec2<T>(a.x - b, a.y - b);
    }
    friend Vec2 operator* (const Vec2 &a, const Vec2 &b){
        return Vec2<T>(a.x * b.x, a.y * b.y);
    }
    friend Vec2 operator* (const Vec2 &a, T b){
        return Vec2<T>(a.x * b, a.y * b);
    }
    friend Vec2 operator/ (const Vec2 &a, const Vec2 &b){
        return Vec2<T>(a.x / b.x, a.y / b.y);
    }
    friend Vec2 operator/ (const Vec2 &a, T b){
        return Vec2<T>(a.x / b, a.y / b);
    }

    Vec2& operator+= (Vec2 const &a){
        x += a.x;
        y += a.y;
        return *this;
    }
    Vec2& operator-= (Vec2 const &a){
        x -= a.x;
        y -= a.y;
        return *this;
    }
    Vec2& operator*= (T v){
        x *= v;
        y *= v;
        return *this;
    }

    bool operator== (Vec2 &a) const{
        return x == a.x && y == a.y;
    }
    bool operator!= (Vec2 &a) const{
        return x != a.x || y != a.y;
    }

    Vec2 norm() const{
        T f = 1.0 / len();
        return Vec2<T>(f * x, f * y);
    }
    T dot(Vec2 const &a) const{
        return x * a.x + y * a.y;
    }
    T len() const{
        return std::sqrt(x * x + y * y);
    }
    T len2() const{
        return x * x + y * y;
    }
};

template<typename T = float>
class Vec3 {
public:
    T x = 0, y = 0, z = 0;

    Vec3() = default;
    explicit Vec3(T v){
        this->x = v;
        this->y = v;
        this->z = v;
    }
    Vec3(T x, T y, T z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3(const Vec2<T>& xy, T z){
        this->x = xy.x;
        this->y = xy.y;
        this->z = z;
    }
    Vec3(const Vec3& v){
        x = v.x;
        y = v.y;
        z = v.z;
    }

    Vec2<T> xy() const{
        return Vec2<T>(x, y);
    }
    Vec2<T> xz() const{
        return Vec2<T>(x, z);
    }
    Vec2<T> yz() const{
        return Vec2<T>(y, z);
    }

    friend Vec3 operator+ (const Vec3 &a, const Vec3 &b){
        return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    friend Vec3 operator+ (const Vec3 &a, T b){
        return Vec3<T>(a.x + b, a.y + b, a.z + b);
    }
    friend Vec3 operator- (const Vec3 &a, const Vec3 &b){
        return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    friend Vec3 operator- (const Vec3 &a, T b){
        return Vec3<T>(a.x - b, a.y - b, a.z - b);
    }
    friend Vec3 operator* (const Vec3 &a, const Vec3 &b){
        return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    friend Vec3 operator* (const Vec3 &a, T b){
        return Vec3<T>(a.x * b, a.y * b, a.z * b);
    }
    friend Vec3 operator/ (const Vec3 &a, const Vec3 &b){
        return Vec3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
    }
    friend Vec3 operator/ (const Vec3 &a, T b){
        return Vec3<T>(a.x / b, a.y / b, a.z / b);
    }

    Vec3 &operator+= (const Vec3 &a){
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }
    Vec3 &operator-= (const Vec3 &a){
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }
    Vec3 &operator*= (T v){

        x *= v;
        y *= v;
        z *= v;
        return *this;
    }

    bool operator== (Vec3 &a) const{
        return x == a.x && y == a.y && z == a.z;
    }
    bool operator!= (Vec3 &a) const{
        return x != a.x || y != a.y || z != a.z;
    }

    Vec3 cross(Vec3 const &a) const{
        T xx = y * a.z - a.y * z;
        T yy = z * a.x - a.z * x;
        T zz = x * a.y - a.x * y;
        return Vec3<T>(xx, yy, zz);
    }
    Vec3 norm() const{
        T lengthSquared = (x * x + y * y + z * z);
        if(lengthSquared == 0)
            return *this;
        T length = 1.0 / std::sqrt(lengthSquared);
        return Vec3<T>(x * length, y * length, z * length);
    }
    T dot(Vec3 const &a) const{
        return x * a.x + y * a.y + z * a.z;
    }
    T len() const{
        return std::sqrt(x * x + y * y + z * z);
    }
    T len2() const{
        return x * x + y * y + z * z;
    }
};

template<typename T = float>
class Vec4 {
public:
    T x = 0, y = 0, z = 0, w = 0;

    Vec4() = default;
    explicit Vec4(T v){
        this->x = v;
        this->y = v;
        this->z = v;
        this->w = v;
    }
    Vec4(T x, T y, T z, T w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    friend Vec4 operator+ (const Vec4 &a, const Vec4 &b){
        return Vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }
    friend Vec4 operator+ (const Vec4 &a, T b){
        return Vec4<T>(a.x + b, a.y + b, a.z + b, a.w + b);
    }
    friend Vec4 operator- (const Vec4 &a, const Vec4 &b){
        return Vec4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }
    friend Vec4 operator- (const Vec4 &a, T b){
        return Vec4<T>(a.x - b, a.y - b, a.z - b, a.w - b);
    }
    friend Vec4 operator* (const Vec4 &a, const Vec4 &b){
        return Vec4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }
    friend Vec4 operator* (const Vec4 &a, T b){
        return Vec4<T>(a.x * b, a.y * b, a.z * b, a.w * b);
    }
    friend Vec4 operator/ (const Vec4 &a, const Vec4 &b){
        return Vec4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
    }
    friend Vec4 operator/ (const Vec4 &a, T b){
        return Vec4<T>(a.x / b, a.y / b, a.z / b, a.w / b);
    }

    Vec4 &operator+= (const Vec4 &a){
        x += a.x;
        y += a.y;
        z += a.z;
        w += a.w;
        return *this;
    }
    Vec4 &operator-= (const Vec4 &a){
        x -= a.x;
        y -= a.y;
        z -= a.z;
        w -= a.w;
        return *this;
    }
    Vec4 &operator*= (T v){
        x *= v;
        y *= v;
        z *= v;
        w *= v;
        return *this;
    }

    bool operator== (Vec4 &a) const{
        return x == a.x && y == a.y && z == a.z && w == a.w;
    }
    bool operator!= (Vec4 &a) const{
        return x != a.x || y != a.y || z != a.z || w != a.w;
    }
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;