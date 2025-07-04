#include "AstrumVector3.hpp"
#include <cmath>

// Origin 정적 멤버 정의
const AstrumVector3 AstrumVector3::Origin = { 0.0f, 0.0f, 0.0f };

float AstrumVector3::Magnitude() const {
    return std::sqrt(X * X + Y * Y + Z * Z);
}

AstrumVector3 AstrumVector3::Normalize() const {
    float mag = Magnitude();
    return (mag == 0.0f) ? *this : (*this / mag);
}

float AstrumVector3::Distance(const AstrumVector3& other) const {
    return std::sqrt(
        (X - other.X) * (X - other.X) +
        (Y - other.Y) * (Y - other.Y) +
        (Z - other.Z) * (Z - other.Z)
    );
}

float AstrumVector3::Dot(const AstrumVector3& other) const {
    return X * other.X + Y * other.Y + Z * other.Z;
}

AstrumVector3 AstrumVector3::Cross(const AstrumVector3& other) const {
    return {
        Y * other.Z - Z * other.Y,
        Z * other.X - X * other.Z,
        X * other.Y - Y * other.X
    };
}

AstrumVector3 AstrumVector3::operator+(const AstrumVector3& v) const {
    return { X + v.X, Y + v.Y, Z + v.Z };
}

AstrumVector3 AstrumVector3::operator-(const AstrumVector3& v) const {
    return { X - v.X, Y - v.Y, Z - v.Z };
}

AstrumVector3 AstrumVector3::operator*(float scalar) const {
    return { X * scalar, Y * scalar, Z * scalar };
}

AstrumVector3 AstrumVector3::operator/(float scalar) const {
    return { X / scalar, Y / scalar, Z / scalar };
}