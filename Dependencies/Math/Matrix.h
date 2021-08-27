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
    explicit Mat4(T v){
        m00 = v;
        m11 = v;
        m22 = v;
        m33 = v;
    }
    Mat4 &identity(){
        m00 = 1.0;
        m11 = 1.0;
        m22 = 1.0;
        m33 = 1.0;
        return *this;
    }
    Mat4 &translate(T x, T y, T z) {
        m30 = m00 * x + m10 * y + m20 * z;
        m31 = m01 * x + m11 * y + m21 * z;
        m32 = m02 * x + m12 * y + m22 * z;

        return *this;
    }
    Mat4 &translate(const Vec3<T> &vector){
        return translate(vector.x, vector.y, vector.z);
    }
    Mat4 &rotate(T angle, T x, T y, T z){
        T angleRadians = angle * RADIANS;
        T c = std::cos(angleRadians);
        T s = std::sin(angleRadians);
        T oneminusc = 1.0 - c;
        T xy = x * y;
        T yz = y * z;
        T xz = x * z;
        T xs = x * s;
        T ys = y * s;
        T zs = z * s;
        T f00 = x * x * oneminusc + c;
        T f2 = xy * oneminusc + zs;
        T f3 = xz * oneminusc - ys;
        T f4 = xy * oneminusc - zs;
        T f5 = y * y * oneminusc + c;
        T f6 = yz * oneminusc + xs;
        T f7 = xz * oneminusc + ys;
        T f8 = yz * oneminusc - xs;
        T f9 = z * z * oneminusc + c;
        T e1 = m00 * f00 + m10 * f2 + m20 * f3;
        T e2 = m01 * f00 + m11 * f2 + m21 * f3;
        T e3 = m02 * f00 + m12 * f2 + m22 * f3;
        T e4 = m03 * f00 + m13 * f2 + m23 * f3;
        T e5 = m00 * f4 + m10 * f5 + m20 * f6;
        T e6 = m01 * f4 + m11 * f5 + m21 * f6;
        T e7 = m02 * f4 + m12 * f5 + m22 * f6;
        T e8 = m03 * f4 + m13 * f5 + m23 * f6;
        T e9 = m00 * f7 + m10 * f8 + m20 * f9;
        T e10 = m01 * f7 + m11 * f8 + m21 * f9;
        T e11 = m02 * f7 + m12 * f8 + m22 * f9;
        T e12 = m03 * f7 + m13 * f8 + m23 * f9;
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
    Mat4 &rotate(T angle, const Vec3<T> &axis){
        return rotate(angle, axis.x, axis.y, axis.z);
    }
    Mat4 &scale(T x, T y, T z){
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
    Mat4 &scale(T s){
        return scale(s, s, s);
    }
    Mat4 &scale(const Vec3<T> &vector){
        return scale(vector.x, vector.y, vector.z);
    }
    Mat4 &multiply(const Mat4& one, const Mat4& two){
        m00 = one.m00 * two.m00 + one.m10 * two.m01 + one.m20 * two.m02 + one.m30 * two.m03;
        m01 = one.m01 * two.m00 + one.m11 * two.m01 + one.m21 * two.m02 + one.m31 * two.m03;
        m02 = one.m02 * two.m00 + one.m12 * two.m01 + one.m22 * two.m02 + one.m32 * two.m03;
        m03 = one.m03 * two.m00 + one.m13 * two.m01 + one.m23 * two.m02 + one.m33 * two.m03;
        m10 = one.m00 * two.m10 + one.m10 * two.m11 + one.m20 * two.m12 + one.m30 * two.m13;
        m11 = one.m01 * two.m10 + one.m11 * two.m11 + one.m21 * two.m12 + one.m31 * two.m13;
        m12 = one.m02 * two.m10 + one.m12 * two.m11 + one.m22 * two.m12 + one.m32 * two.m13;
        m13 = one.m03 * two.m10 + one.m13 * two.m11 + one.m23 * two.m12 + one.m33 * two.m13;
        m20 = one.m00 * two.m20 + one.m10 * two.m21 + one.m20 * two.m22 + one.m30 * two.m23;
        m21 = one.m01 * two.m20 + one.m11 * two.m21 + one.m21 * two.m22 + one.m31 * two.m23;
        m22 = one.m02 * two.m20 + one.m12 * two.m21 + one.m22 * two.m22 + one.m32 * two.m23;
        m23 = one.m03 * two.m20 + one.m13 * two.m21 + one.m23 * two.m22 + one.m33 * two.m23;
        m30 = one.m00 * two.m30 + one.m10 * two.m31 + one.m20 * two.m32 + one.m30 * two.m33;
        m31 = one.m01 * two.m30 + one.m11 * two.m31 + one.m21 * two.m32 + one.m31 * two.m33;
        m32 = one.m02 * two.m30 + one.m12 * two.m31 + one.m22 * two.m32 + one.m32 * two.m33;
        m33 = one.m03 * two.m30 + one.m13 * two.m31 + one.m23 * two.m32 + one.m33 * two.m33;

        return *this;
    }
    Mat4 &multiply(const Mat4& matrix){
        return multiply(*this, matrix);
    }
    T determinant3x3(T t00, T t01, T t02, T t10, T t11, T t12, T t20, T t21, T t22) {
        return   t00 * (t11 * t22 - t12 * t21)
                 + t01 * (t12 * t20 - t10 * t22)
                 + t02 * (t10 * t21 - t11 * t20);
    }
    Mat4 &invert(){
        T f = m00 * ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32)
                     - m13 * m22 * m31- m11 * m23 * m32- m12 * m21 * m33);
        f -= m01 * ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32)
                    - m13 * m22 * m30- m10 * m23 * m32- m12 * m20 * m33);
        f += m02 * ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31)
                    - m13 * m21 * m30- m10 * m23 * m31- m11 * m20 * m33);
        f -= m03 * ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31)
                    - m12 * m21 * m30- m10 * m22 * m31- m11 * m20 * m32);
        T determinant_inv = 1.0 / f;

        T t00 =  determinant3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33);
        T t01 = -determinant3x3(m10, m12, m13, m20, m22, m23, m30, m32, m33);
        T t02 =  determinant3x3(m10, m11, m13, m20, m21, m23, m30, m31, m33);
        T t03 = -determinant3x3(m10, m11, m12, m20, m21, m22, m30, m31, m32);

        T t10 = -determinant3x3(m01, m02, m03, m21, m22, m23, m31, m32, m33);
        T t11 =  determinant3x3(m00, m02, m03, m20, m22, m23, m30, m32, m33);
        T t12 = -determinant3x3(m00, m01, m03, m20, m21, m23, m30, m31, m33);
        T t13 =  determinant3x3(m00, m01, m02, m20, m21, m22, m30, m31, m32);

        T t20 =  determinant3x3(m01, m02, m03, m11, m12, m13, m31, m32, m33);
        T t21 = -determinant3x3(m00, m02, m03, m10, m12, m13, m30, m32, m33);
        T t22 =  determinant3x3(m00, m01, m03, m10, m11, m13, m30, m31, m33);
        T t23 = -determinant3x3(m00, m01, m02, m10, m11, m12, m30, m31, m32);

        T t30 = -determinant3x3(m01, m02, m03, m11, m12, m13, m21, m22, m23);
        T t31 =  determinant3x3(m00, m02, m03, m10, m12, m13, m20, m22, m23);
        T t32 = -determinant3x3(m00, m01, m03, m10, m11, m13, m20, m21, m23);
        T t33 =  determinant3x3(m00, m01, m02, m10, m11, m12, m20, m21, m22);

        m00 = t00 * determinant_inv;
        m11 = t11 * determinant_inv;
        m22 = t22 * determinant_inv;
        m33 = t33 * determinant_inv;
        m01 = t10 * determinant_inv;
        m10 = t01 * determinant_inv;
        m20 = t02 * determinant_inv;
        m02 = t20 * determinant_inv;
        m12 = t21 * determinant_inv;
        m21 = t12 * determinant_inv;
        m03 = t30 * determinant_inv;
        m30 = t03 * determinant_inv;
        m13 = t31 * determinant_inv;
        m31 = t13 * determinant_inv;
        m32 = t23 * determinant_inv;
        m23 = t32 * determinant_inv;

        return *this;
    }
    Mat4 &removeTranslation(){
        m30 = 0.0;
        m31 = 0.0;
        m32 = 0.0;
        return *this;
    }
    Mat4 &orthographic(T left, T right, T bottom, T top, T near, T far){
        m00 = 2.0 / (right - left);
        m11 = 2.0 / (top - bottom);
        m22 = 2.0 / (near - far);

        m30 = (left + right) / (left - right);
        m31 = (bottom + top) / (bottom - top);
        m32 = (far + near) / (far - near);

        return *this;
    }
    Mat4 &perspective(T fov, T width, T height, T near, T far){
        T aspectRatio = width / height;
        T yScale = std::tan(fov / 2.0 * RADIANS);

        m00 = 1.0 / (aspectRatio * yScale);
        m11 = 1.0 / (yScale);
        m22 = far / (near - far);
        m23 = -1.0;
        m32 = -(far * near) / (far - near);

        return *this;
    }
    Mat4 &lookAt(const Vec3<T> &eye, const Vec3<T> &center, const Vec3<T> &up){
        Vec3 f = (center - eye).norm();
        Vec3 s = (f.cross(up)).norm();
        Vec3 u = s.cross(f);

        m00 = s.x;
        m10 = s.y;
        m20 = s.z;
        m01 = u.x;
        m11 = u.y;
        m21 = u.z;
        m02 =-f.x;
        m12 =-f.y;
        m22 =-f.z;
        m30 =-s.dot(eye);
        m31 =-u.dot(eye);
        m32 = f.dot(eye);

        return *this;
    }

    char *toString() {
        const char *mt = "|%+6.2f %+6.2f %+6.2f %+6.2f|\n|%+6.2f %+6.2f %+6.2f %+6.2f|\n|%+6.2f %+6.2f %+6.2f %+6.2f|\n|%+6.2f %+6.2f %+6.2f %+6.2f|\n";
        char *s = (char *) malloc(sizeof(char) * 128);
        std::sprintf(s, mt, m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
        return s;
    }
    const T* getBuffer() const {
        return &m00;
    }
    T* getBuffer(){
        return &m00;
    }

    ~Mat4() = default;
};

template<typename T = float>
Mat4<T> identityMatrix(){
    return Mat4<T>(1.0);
}
template<typename T = float>
Mat4<T> perspectiveMatrix(T fov, T width, T height, T near, T far){
    Mat4<T> mat = identityMatrix();
    T aspectRatio = width / height;
    T yScale = std::tan(fov / 2.0 * RADIANS);

    mat.m00 = 1.0 / (aspectRatio * yScale);
    mat.m11 = 1.0 / (yScale);
    mat.m22 = far / (near - far);
    mat.m23 = -1.0;
    mat.m32 = -(far * near) / (far - near);

    return mat;
}
template<typename T = float>
Mat4<T> orthographicMatrix(T left, T right, T bottom, T top, T near, T far){
    Mat4<T> mat = identityMatrix();

    mat.m00 = 2.0 / (right - left);
    mat.m11 = 2.0 / (top - bottom);
    mat.m22 = 2.0 / (near - far);

    mat.m30 = (left + right) / (left - right);
    mat.m31 = (bottom + top) / (bottom - top);
    mat.m32 = (far + near) / (far - near);

    return mat;
}
template<typename T = float>
Mat4<T> multiplyMatrix(const Mat4<T>& one, const Mat4<T>& two){
    Mat4<T> mat = one;

    mat.m00 = mat.m00 * two.m00 + mat.m10 * two.m01 + mat.m20 * two.m02 + mat.m30 * two.m03;
    mat.m01 = mat.m01 * two.m00 + mat.m11 * two.m01 + mat.m21 * two.m02 + mat.m31 * two.m03;
    mat.m02 = mat.m02 * two.m00 + mat.m12 * two.m01 + mat.m22 * two.m02 + mat.m32 * two.m03;
    mat.m03 = mat.m03 * two.m00 + mat.m13 * two.m01 + mat.m23 * two.m02 + mat.m33 * two.m03;
    mat.m10 = mat.m00 * two.m10 + mat.m10 * two.m11 + mat.m20 * two.m12 + mat.m30 * two.m13;
    mat.m11 = mat.m01 * two.m10 + mat.m11 * two.m11 + mat.m21 * two.m12 + mat.m31 * two.m13;
    mat.m12 = mat.m02 * two.m10 + mat.m12 * two.m11 + mat.m22 * two.m12 + mat.m32 * two.m13;
    mat.m13 = mat.m03 * two.m10 + mat.m13 * two.m11 + mat.m23 * two.m12 + mat.m33 * two.m13;
    mat.m20 = mat.m00 * two.m20 + mat.m10 * two.m21 + mat.m20 * two.m22 + mat.m30 * two.m23;
    mat.m21 = mat.m01 * two.m20 + mat.m11 * two.m21 + mat.m21 * two.m22 + mat.m31 * two.m23;
    mat.m22 = mat.m02 * two.m20 + mat.m12 * two.m21 + mat.m22 * two.m22 + mat.m32 * two.m23;
    mat.m23 = mat.m03 * two.m20 + mat.m13 * two.m21 + mat.m23 * two.m22 + mat.m33 * two.m23;
    mat.m30 = mat.m00 * two.m30 + mat.m10 * two.m31 + mat.m20 * two.m32 + mat.m30 * two.m33;
    mat.m31 = mat.m01 * two.m30 + mat.m11 * two.m31 + mat.m21 * two.m32 + mat.m31 * two.m33;
    mat.m32 = mat.m02 * two.m30 + mat.m12 * two.m31 + mat.m22 * two.m32 + mat.m32 * two.m33;
    mat.m33 = mat.m03 * two.m30 + mat.m13 * two.m31 + mat.m23 * two.m32 + mat.m33 * two.m33;

    return mat;
}
template<typename T = float>
Mat4<T> lookAtMatrix(const Vec3<T> &eye, const Vec3<T> &center, const Vec3<T> &up){
    Mat4<T> mat = identityMatrix();
    Vec3 f = (center - eye).norm();
    Vec3 s = (f.cross(up)).norm();
    Vec3 u = s.cross(f);

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
    mat.m32 = f.dot(eye);

    return mat;
}

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;