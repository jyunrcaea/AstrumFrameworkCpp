#pragma once
#include <numbers>
#include <cmath>
#include "AstrumVector3.hpp"

struct AstrumQuaternion {
    float W, X, Y, Z;

    static AstrumQuaternion Identity();

    static AstrumQuaternion FromAxisAngle(AstrumVector3 axis, float rad);
    static AstrumQuaternion FromEuler(AstrumVector3 deg);
    AstrumQuaternion operator*(const AstrumQuaternion& rhs) const;
    AstrumQuaternion operator*(float scalar) const;
    AstrumQuaternion& operator*=(float scalar);

    AstrumVector3 Rotate(const AstrumVector3& v) const;
    AstrumQuaternion Normalized() const;
    AstrumQuaternion Conjugate() const;
    AstrumQuaternion Inverse() const;
};