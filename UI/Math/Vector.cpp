#include <cmath>

#include "Vector.h"

Vec2f::Vec2f(float v) {
	this->x = v;
	this->y = v;
}

Vec2f::Vec2f(float x, float y) {
	this->x = z;
	this->y = y;
}

Vec2f::Vec2f(Vec2f &v) {
	this->x = v.x;
	this->y = v.y;
}

Vec2f operator+ (Vec2f &a, Vec2f &b) {
	return Vec2f(a.x + b.x, a.y + b.y);
}

Vec2f operator- (Vec2f &a, Vec2f &b) {
	return Vec2f(a.x - b.x, a.y - b.y);
}
	
Vec2f Vec2f::operator+= (Vec2f &a) {
	x += a.x;
	y += a.y;
	return this;
}

Vec2f Vec2f::operator-= (Vec2f &a) {
	x -= a.x;
	y -= a.y;
	return this;
}

Vec2f Vec2f::operator*= (float v) {
	x *= v;
	y *= v;
	return this;
}
	
bool Vec2f::operator== (Vec2f &a) {
	return x == a.x && y == a.y;
}

bool Vec2f::operator!= (Vec2f &a) {
	return x != a.x || y != a.y;
}

Vec2f Vec2f::norm() {
	float f = 1f / len();
	return Vec2f(f * x, f * y);
}

float Vec2f::dot(Vec2f &a) {
	return x * a.x + y * a.y;
}

float Vec2f::len() {
	return std::sqrt(x * x + y * y);
}

Vec3f::Vec3f(float v) {
	x = v;
	y = v;
	z = v;
}

Vec3f::Vec3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3f::Vec3f(Vec2f& xy, float z) {
	this->x = xy.x;
	this->y = xy.y;
	this->z = z;
}

Vec3f::Vec3f(Vec3f& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

Vec2f Vec3f::xy() {
	return Vec2f(x, y);
}

Vec2f Vec3f::xz() {
	return Vec2f(x, z);
}

Vec2f Vec3f::yz() {
	return Vec2f(y, z);
}

Vec3f operator+ (Vec3f &a, Vec3f &b) {
	return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3f operator- (Vec3f &a, Vec3f &b) {
	return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}
	
Vec3f Vec3f::operator+= (Vec3f &a) {
	x += a.x;
	y += a.y;
	z += a.z;
	return this;
}

Vec3f Vec3f::operator-= (Vec3f &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return this;
}

Vec3f Vec3f::operator*= (float v) {
	x *= v;
	y *= v;
	z *= v;
	return this; 
}
	
bool Vec3f::operator== (Vec3f &a) {
	return x == a.x && y == a.y && z == a.z;
}

bool Vec3f::operator!= (Vec3f &a) {
	return x != a.x || y != a.y || z != a.z;
}

Vec3f Vec3f::cross(Vec3f &a) {
	float xx = left.y * right.z - right.y * left.z;
    float yy = left.z * right.x - right.z * left.x;
    float zz = left.x * right.y - right.x * left.y;
	return Vec3f(xx, yy, zz);
}

Vec3f Vec3f::norm() {
	float f = 1f / len();
	return Vec3f(x * f, y * f, z * f);
}

float Vec3f::dot(Vec3f &a) {
	return x * a.x + y * a.y + z * a.z;
}

float Vec3f::len() {
	return std::sqrt(x * x + y * y + z * z);
}