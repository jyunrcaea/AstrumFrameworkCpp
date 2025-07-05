#include "AstrumVector4.hpp"
#include <cmath>

// Origin 정적 멤버 정의
const AstrumVector4 AstrumVector4::Origin = { 0.0f, 0.0f, 0.0f, 0.0f };

float AstrumVector4::Magnitude() const {
    return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

AstrumVector4 AstrumVector4::Normalize() const {
    float mag = Magnitude();
    return (mag == 0.0f) ? *this : (*this / mag);
}

float AstrumVector4::Distance(const AstrumVector4& other) const {
    return std::sqrt(
        (X - other.X) * (X - other.X) +
        (Y - other.Y) * (Y - other.Y) +
        (Z - other.Z) * (Z - other.Z) +
        (W - other.W) * (W - other.W)
    );
}

float AstrumVector4::Dot(const AstrumVector4& other) const {
    return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
}

AstrumVector4 AstrumVector4::operator+(const AstrumVector4& v) const {
    return { X + v.X, Y + v.Y, Z + v.Z, W + v.W };
}

AstrumVector4 AstrumVector4::operator-(const AstrumVector4& v) const {
    return { X - v.X, Y - v.Y, Z - v.Z, W - v.W };
}

AstrumVector4 AstrumVector4::operator*(float scalar) const {
    return { X * scalar, Y * scalar, Z * scalar, W * scalar };
}

AstrumVector4 AstrumVector4::operator/(float scalar) const {
    return { X / scalar, Y / scalar, Z / scalar, W / scalar };
}