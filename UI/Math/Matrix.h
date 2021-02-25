#pragma once

class Mat4f {
public:
	float m00 = 0.0f;
	float m01 = 0.0f;
	float m02 = 0.0f;
	float m03 = 0.0f;
	float m10 = 0.0f;
	float m11 = 0.0f;
	float m12 = 0.0f;
	float m13 = 0.0f;
	float m20 = 0.0f;
	float m21 = 0.0f;
	float m22 = 0.0f;
	float m23 = 0.0f;
	float m30 = 0.0f;
	float m31 = 0.0f;
	float m32 = 0.0f;
	float m33 = 0.0f;

	Mat4f() = default;
	explicit Mat4f(float v);

	Mat4f &rotate(float angle, const Vec3f &axis);
	Mat4f &rotate(float angle, float x, float y, float z);
	Mat4f &scale(float scale);
	Mat4f &scale(float x, float y, float z);
	Mat4f &scale(const Vec3f &scale);
	Mat4f &translate(const Vec3f &vector);
	Mat4f &translate(float x, float y, float z);

	const std::string toString();
};

Mat4f identityMatrix();
Mat4f perspective(float fov, float width, float height, float near, float far);
Mat4f orthographic(float left, float right, float bottom, float top, float near, float far);
Mat4f lookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
