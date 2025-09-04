#pragma once
#pragma once
#include <string>
#include <format>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numbers>

struct AstrumLongVector2
{
    long long int X = 0.0;
    long long int Y = 0.0;

    constexpr AstrumLongVector2() = default;
    constexpr AstrumLongVector2(long long x, long long y) noexcept : X(x), Y(y) {}

    double Magnitude() const noexcept { return std::sqrt(X * X + Y * Y); }
    double Distance(const AstrumLongVector2& other) const noexcept {
        const long dx = X - other.X, dy = Y - other.Y;
        return std::sqrt(dx * dx + dy * dy);
    }
    constexpr double Dot(const AstrumLongVector2& other) const noexcept { return X * other.X + Y * other.Y; }

    constexpr AstrumLongVector2 operator+(const AstrumLongVector2& v) const noexcept { return { X + v.X, Y + v.Y }; }
    constexpr AstrumLongVector2 operator-(const AstrumLongVector2& v) const noexcept { return { X - v.X, Y - v.Y }; }
    constexpr AstrumLongVector2 operator*(const AstrumLongVector2& v) const noexcept { return { X * v.X, Y * v.Y }; }
    constexpr AstrumLongVector2 operator/(const AstrumLongVector2& v) const noexcept { return { X / v.X, Y / v.Y }; }

    constexpr AstrumLongVector2 operator*(long long scalar) const noexcept { return { X * scalar, Y * scalar }; }
    constexpr AstrumLongVector2 operator/(long long scalar) const noexcept { return { X / scalar, Y / scalar }; }
    friend constexpr AstrumLongVector2 operator*(long long scalar, const AstrumLongVector2& v) noexcept { return { v.X * scalar, v.Y * scalar }; }

    AstrumLongVector2& operator+=(const AstrumLongVector2& v) noexcept { X += v.X; Y += v.Y; return *this; }
    AstrumLongVector2& operator-=(const AstrumLongVector2& v) noexcept { X -= v.X; Y -= v.Y; return *this; }
    AstrumLongVector2& operator*=(const AstrumLongVector2& v) noexcept { X *= v.X; Y *= v.Y; return *this; }
    AstrumLongVector2& operator/=(const AstrumLongVector2& v) noexcept { X /= v.X; Y /= v.Y; return *this; }
    AstrumLongVector2& operator*=(long long scalar) noexcept { X *= scalar; Y *= scalar; return *this; }
    AstrumLongVector2& operator/=(long long scalar) noexcept { X /= scalar; Y /= scalar; return *this; }

    constexpr long long GetMinimum() const noexcept { return (std::min)(X, Y); }
    constexpr long long GetMaximum() const noexcept { return (std::max)(X, Y); }

    static const AstrumLongVector2 Origin;
};

inline constexpr AstrumLongVector2 AstrumLongVector2::Origin = { 0, 0 };

inline std::ostream& operator<<(std::ostream& os, const AstrumLongVector2& p) {
    os << "AstrumLongVector2(" << p.X << ", " << p.Y << ")";
    return os;
}