#include <cstdio>
#include <cmath>
#include <string>

#include "Vector.h"
#include "Matrix.h"

#define RADIANS 0.01745329251994329576923690768489f

Mat4f::Mat4f(float v) {
	m00 = v;
	m11 = v;
	m22 = v;
	m33 = v;
}

Mat4f &Mat4f::rotate(float angle, const Vec3f &axis) {
	return rotate(angle, axis.x, axis.y, axis.z);
}

Mat4f &Mat4f::rotate(float angle, float x, float y, float z) {
	float angleRadians = angle * RADIANS;
	float c = std::cos(angleRadians);
	float s = std::sin(angleRadians);
	float oneminusc = 1.0f - c;
	float xy = x * y;
	float yz = y * z;
	float xz = x * z;
	float xs = x * s;
	float ys = y * s;
	float zs = z * s;
	float f00 = x * x * oneminusc + c;
	float f2 = xy * oneminusc + zs;
	float f3 = xz * oneminusc - ys;
	float f4 = xy * oneminusc - zs;
	float f5 = y * y * oneminusc + c;
	float f6 = yz * oneminusc + xs;
	float f7 = xz * oneminusc + ys;
	float f8 = yz * oneminusc - xs;
	float f9 = z * z * oneminusc + c;
	float e1 = m00 * f00 + m10 * f2 + m20 * f3;
	float e2 = m01 * f00 + m11 * f2 + m21 * f3;
	float e3 = m02 * f00 + m12 * f2 + m22 * f3;
	float e4 = m03 * f00 + m13 * f2 + m23 * f3;
	float e5 = m00 * f4 + m10 * f5 + m20 * f6;
	float e6 = m01 * f4 + m11 * f5 + m21 * f6;
	float e7 = m02 * f4 + m12 * f5 + m22 * f6;
	float e8 = m03 * f4 + m13 * f5 + m23 * f6;
	float e9 = m00 * f7 + m10 * f8 + m20 * f9;
	float e10 = m01 * f7 + m11 * f8 + m21 * f9;
	float e11 = m02 * f7 + m12 * f8 + m22 * f9;
	float e12 = m03 * f7 + m13 * f8 + m23 * f9;
	m00 = e1;
	m01 = e2;
	m02 = e3;
	m03 = e4;
	m10 = e5;
	m11 = e6;
	m12 = e7;
	m13 = e8;
	m20 = e9;
	m21 = e10;
	m22 = e11;
	m23 = e12;
	return *this;
}

Mat4f &Mat4f::scale(float s) {
	return scale(s, s, s);
}

Mat4f &Mat4f::scale(float x, float y, float z) {
	m00 *= x;
	m01 *= x;
	m02 *= x;
	m03 *= x;
	m10 *= y;
	m11 *= y;
	m12 *= y;
	m13 *= y;
	m20 *= z;
	m21 *= z;
	m22 *= z;
	m23 *= z;
	return *this;
}

Mat4f &Mat4f::scale(const Vec3f &v) {
	return scale(v.x, v.y, v.z);
}

Mat4f &Mat4f::translate(const Vec3f &v) {
	return translate(v.x, v.y, v.z);
}

Mat4f &Mat4f::translate(float x, float y, float z) {
	m30 += m00 * x + m10 * y + m20 * z + m30;
	m31 += m01 * x + m11 * y + m21 * z + m31;
	m32 += m02 * x + m12 * y + m22 * z + m32;
	m33 += m03 * x + m13 * y + m23 * z + m33;
	return *this;
}

std::string Mat4f::toString() const {
	const char *fmt = "|%+6.2f %+6.2f %+6.2f %+6.2f|\n|%+6.2f %+6.2f %+6.2f %+6.2f|\n|%+6.2f %+6.2f %+6.2f %+6.2f|\n|%+6.2f %+6.2f %+6.2f %+6.2f|\n";
	char s[128];
	std::sprintf(s, fmt, m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	return s;
}

Mat4f identityMatrix() {
	return Mat4f(1.0f);
}

Mat4f perspectiveMatrix(float fov, float width, float height, float near, float far) {
	Mat4f mat = identityMatrix();
	float aspectRatio = width / height;
	float yScale = std::tan(fov / 2.0f * RADIANS);

	mat.m00 = 1.0f / (aspectRatio * yScale);
	mat.m11 = 1.0f / (yScale);
	mat.m22 = far / (near - far);
	mat.m23 = -1.0f;
	mat.m32 = -(far * near) / (far - near);
	return mat;
}

Mat4f orthographicMatrix(float left, float right, float bottom, float top, float near, float far) {
	Mat4f mat = identityMatrix();

	mat.m00 = 2.0f / (right - left);
	mat.m11 = 2.0f / (top - bottom);
	mat.m22 = 2.0f / (near - far);

	mat.m30 = (left + right) / (left - right);
	mat.m31 = (bottom + top) / (bottom - top);
	mat.m32 = (far + near) / (far - near);

	return mat;
}

Mat4f lookAtMatrix(const Vec3f &eye, const Vec3f &center, const Vec3f &up) {
	Mat4f mat = identityMatrix();
	Vec3f f = (center - eye).norm();
	Vec3f s = (f.cross(up)).norm();
	Vec3f u = s.cross(f);

	mat.m00 = s.x;
	mat.m10 = s.y;
	mat.m20 = s.z;
	mat.m01 = u.x;
	mat.m11 = u.y;
	mat.m21 = u.z;
	mat.m02 =-f.x;
	mat.m12 =-f.y;
	mat.m22 =-f.z;
	mat.m30 =-s.dot(eye);
	mat.m31 =-u.dot(eye);
	mat.m32 =f.dot(eye);

	return mat;
}
