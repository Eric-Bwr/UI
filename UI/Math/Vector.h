#pragma once

class Vec2f {
public:
	float x, y;

	explicit Vec2f(float v);
	Vec2f(float x, float y);
	Vec2f(Vec2f &v);

	friend Vec2f operator+ (Vec2f &a, Vec2f &b);
	friend Vec2f operator- (Vec2f &a, Vec2f &b);
	
	Vec2f operator+= (Vec2f &a);
	Vec2f operator-= (Vec2f &a);
	Vec2f operator*= (float v);
	
	bool operator== (Vec2f &a) const;
	bool operator!= (Vec2f &a) const;

	Vec2f norm() const;
	float dot(Vec2f& a) const;
	float len() const;
};

class Vec3f {
public:
	float x, y, z;

	explicit Vec3f(float v);
	Vec3f(float x, float y, float z);
	Vec3f(Vec2f& xy, float z);
	Vec3f(Vec3f& v);

	Vec2f xy() const;
	Vec2f xz() const;
	Vec2f yz() const;

	friend Vec3f operator+ (Vec3f &a, Vec3f &b);
	friend Vec3f operator- (Vec3f &a, Vec3f &b);
	
	Vec3f operator+= (Vec3f &a);
	Vec3f operator-= (Vec3f &a);
	Vec3f operator*= (float v);
	
	bool operator== (Vec3f &a) const;
	bool operator!= (Vec3f &a) const;

	Vec3f cross(Vec3f &a) const;
	Vec3f norm() const;
	float dot(Vec3f &a) const;
	float len() const;
};