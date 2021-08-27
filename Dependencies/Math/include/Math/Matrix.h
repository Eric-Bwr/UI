#pragma once

#include <cstdio>
#include <cmath>
#include "Vector.h"

template<typename T = float>
class Mat4 {
public:
    T m00 = 0.0;
    T m01 = 0.0;
    T m02 = 0.0;
    T m03 = 0.0;
    T m10 = 0.0;
    T m11 = 0.0;
    T m12 = 0.0;
    T m13 = 0.0;
    T m20 = 0.0;
    T m21 = 0.0;
    T m22 = 0.0;
    T m23 = 0.0;
    T m30 = 0.0;
    T m31 = 0.0;
    T m32 = 0.0;
    T m33 = 0.0;

    Mat4() = default;
    explicit Mat4(T v);

    Mat4 &identity();
    Mat4 &translate(const Vec3<T> &vector);
    Mat4 &translate(T x, T y, T z);
    Mat4 &rotate(T angle, const Vec3<T> &axis);
    Mat4 &rotate(T angle, T x, T y, T z);
    Mat4 &scale(T scale);
    Mat4 &scale(T x, T y, T z);
    Mat4 &scale(const Vec3<T> &scale);
    Mat4 &multiply(const Mat4& matrix);
    Mat4 &multiply(const Mat4& one, const Mat4& two);
    Mat4 &invert();
    Mat4 &removeTranslation();
    Mat4 &orthographic(T left, T right, T bottom, T top, T near, T far);
    Mat4 &perspective(T fov, T width, T height, T near, T far);
    Mat4 &lookAt(const Vec3<T> &eye, const Vec3<T> &center, const Vec3<T> &up);

    char *toString() const;
    const T* getBuffer() const;
    T* getBuffer();

    ~Mat4() = default;
};

template<typename T = float>
Mat4<T> identityMatrix();
template<typename T = float>
Mat4<T> perspectiveMatrix(T fov, T width, T height, T near, T far);
template<typename T = float>
Mat4<T> orthographicMatrix(T left, T right, T bottom, T top, T near, T far);
template<typename T = float>
Mat4<T> multiplyMatrix(const Mat4<T>& one, const Mat4<T>& two);
template<typename T = float>
Mat4<T> lookAtMatrix(const Vec3<T> &eye, const Vec3<T> &center, const Vec3<T> &up);

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;
