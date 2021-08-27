#pragma once

#include <cmath>

#ifndef radians
#define radians 0.01745329251994329576923690768489
#endif

template<typename T = float>
class Vec2 {
public:
	T x = 0, y = 0;

	Vec2() = default;
	explicit Vec2(T v);
	Vec2(T x, T y);
	Vec2(const Vec2 &v);

	friend Vec2 operator+ (const Vec2 &a, const Vec2 &b);
	friend Vec2 operator+ (const Vec2 &a, T b);
	friend Vec2 operator- (const Vec2 &a, const Vec2 &b);
	friend Vec2 operator- (const Vec2 &a, T b);
	friend Vec2 operator* (const Vec2 &a, const Vec2 &b);
	friend Vec2 operator* (const Vec2 &a, T b);
	friend Vec2 operator/ (const Vec2 &a, const Vec2 &b);
	friend Vec2 operator/ (const Vec2 &a, T b);

	Vec2& operator+= (Vec2 const &a);
	Vec2& operator-= (Vec2 const &a);
	Vec2& operator*= (T v);
	
	bool operator== (Vec2 &a) const;
	bool operator!= (Vec2 &a) const;

	Vec2 norm() const;
	T dot(Vec2 const &a) const;
	T len() const;
	T len2() const;
};

template<typename T = float>
class Vec3 {
public:
	T x = 0, y = 0, z = 0;

	Vec3() = default;
	explicit Vec3(T v);
	Vec3(T x, T y, T z);
	Vec3(const Vec2<T>& xy, T z);
	Vec3(const Vec3& v);

	Vec2<T> xy() const;
	Vec2<T> xz() const;
	Vec2<T> yz() const;

	friend Vec3 operator+ (const Vec3 &a, const Vec3 &b);
	friend Vec3 operator+ (const Vec3 &a, T b);
	friend Vec3 operator- (const Vec3 &a, const Vec3 &b);
	friend Vec3 operator- (const Vec3 &a, T b);
	friend Vec3 operator* (const Vec3 &a, const Vec3 &b);
	friend Vec3 operator* (const Vec3 &a, T b);
	friend Vec3 operator/ (const Vec3 &a, const Vec3 &b);
	friend Vec3 operator/ (const Vec3 &a, T b);

	Vec3 &operator+= (const Vec3 &a);
	Vec3 &operator-= (const Vec3 &a);
	Vec3 &operator*= (T v);
	
	bool operator== (Vec3 &a) const;
	bool operator!= (Vec3 &a) const;

	Vec3 cross(Vec3 const &a) const;
	Vec3 norm() const;
	T dot(Vec3 const &a) const;
	T len() const;
	T len2() const;
};

template<typename T = float>
class Vec4 {
public:
    T x = 0, y = 0, z = 0, w = 0;

	Vec4() = default;
    explicit Vec4(T v);
    Vec4(T x, T y, T z, T w);

    friend Vec4 operator+ (const Vec4 &a, const Vec4 &b);
    friend Vec4 operator+ (const Vec4 &a, T b);
    friend Vec4 operator- (const Vec4 &a, const Vec4 &b);
    friend Vec4 operator- (const Vec4 &a, T b);
    friend Vec4 operator* (const Vec4 &a, const Vec4 &b);
    friend Vec4 operator* (const Vec4 &a, T b);
    friend Vec4 operator/ (const Vec4 &a, const Vec4 &b);
    friend Vec4 operator/ (const Vec4 &a, T b);

    Vec4 &operator+= (const Vec4 &a);
    Vec4 &operator-= (const Vec4 &a);
    Vec4 &operator*= (T v);

    bool operator== (Vec4 &a) const;
    bool operator!= (Vec4 &a) const;
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