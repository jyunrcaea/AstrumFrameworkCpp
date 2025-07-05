#pragma once
#include <cmath>

struct AstrumVector2 {
    float X = 0.0f;
    float Y = 0.0f;

    constexpr AstrumVector2() = default;
    constexpr AstrumVector2(float x, float y) : X(x), Y(y) {}

    float Magnitude() const { return std::sqrt(X * X + Y * Y); }

    AstrumVector2 Normalize() const {
        float mag = Magnitude();
        return (mag == 0.0f) ? *this : (*this / mag);
    }

    float Distance(const AstrumVector2& other) const {
        return std::sqrt((X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y));
    }

    float Dot(const AstrumVector2& other) const {
        return X * other.X + Y * other.Y;
    }

    inline static const AstrumVector2 Origin = { 0, 0 };

    // Operators
    AstrumVector2 operator+(const AstrumVector2& v) const { return { X + v.X, Y + v.Y }; }
    AstrumVector2 operator-(const AstrumVector2& v) const { return { X - v.X, Y - v.Y }; }
    AstrumVector2 operator*(float scalar) const { return { X * scalar, Y * scalar }; }
    AstrumVector2 operator/(float scalar) const { return { X / scalar, Y / scalar }; }
};
