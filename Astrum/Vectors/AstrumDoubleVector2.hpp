#pragma once
#include <string>
#include <format>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numbers>

struct AstrumDoubleVector2 {
    double X = 0.0;
    double Y = 0.0;

    constexpr AstrumDoubleVector2() = default;
    constexpr AstrumDoubleVector2(double x, double y) noexcept : X(x), Y(y) {}

    double Magnitude() const noexcept { return std::sqrt(X * X + Y * Y); }
    AstrumDoubleVector2 Normalize() const noexcept {
        const double mag = Magnitude();
        return (mag == 0.0) ? *this : (*this / mag);
    }
    double Distance(const AstrumDoubleVector2& other) const noexcept {
        const double dx = X - other.X, dy = Y - other.Y;
        return std::sqrt(dx * dx + dy * dy);
    }
    constexpr double Dot(const AstrumDoubleVector2& other) const noexcept { return X * other.X + Y * other.Y; }

    AstrumDoubleVector2 Rotate(AstrumDoubleVector2 pivot, double rotationDegrees) const noexcept {
        const double rad = rotationDegrees * std::numbers::pi_v<double> / 180.0;
        const double c = std::cos(rad), s = std::sin(rad);
        const double dx = X - pivot.X, dy = Y - pivot.Y;
        return {
            pivot.X + dx * c - dy * s,
            pivot.Y + dx * s + dy * c
        };
    }

    constexpr AstrumDoubleVector2 operator+(const AstrumDoubleVector2& v) const noexcept { return { X + v.X, Y + v.Y }; }
    constexpr AstrumDoubleVector2 operator-(const AstrumDoubleVector2& v) const noexcept { return { X - v.X, Y - v.Y }; }
    constexpr AstrumDoubleVector2 operator*(const AstrumDoubleVector2& v) const noexcept { return { X * v.X, Y * v.Y }; }
    constexpr AstrumDoubleVector2 operator/(const AstrumDoubleVector2& v) const noexcept { return { X / v.X, Y / v.Y }; }

    constexpr AstrumDoubleVector2 operator*(double scalar) const noexcept { return { X * scalar, Y * scalar }; }
    constexpr AstrumDoubleVector2 operator/(double scalar) const noexcept { return { X / scalar, Y / scalar }; }
    friend constexpr AstrumDoubleVector2 operator*(double scalar, const AstrumDoubleVector2& v) noexcept { return { v.X * scalar, v.Y * scalar }; }

    AstrumDoubleVector2& operator+=(const AstrumDoubleVector2& v) noexcept { X += v.X; Y += v.Y; return *this; }
    AstrumDoubleVector2& operator-=(const AstrumDoubleVector2& v) noexcept { X -= v.X; Y -= v.Y; return *this; }
    AstrumDoubleVector2& operator*=(const AstrumDoubleVector2& v) noexcept { X *= v.X; Y *= v.Y; return *this; }
    AstrumDoubleVector2& operator/=(const AstrumDoubleVector2& v) noexcept { X /= v.X; Y /= v.Y; return *this; }
    AstrumDoubleVector2& operator*=(double scalar) noexcept { X *= scalar; Y *= scalar; return *this; }
    AstrumDoubleVector2& operator/=(double scalar) noexcept { X /= scalar; Y /= scalar; return *this; }

    constexpr double GetMinimum() const noexcept { return (std::min)(X, Y); }
    constexpr double GetMaximum() const noexcept { return (std::max)(X, Y); }

    static const AstrumDoubleVector2 Origin;
};

inline constexpr AstrumDoubleVector2 AstrumDoubleVector2::Origin = { 0, 0 };

inline std::ostream& operator<<(std::ostream& os, const AstrumDoubleVector2& p) {
    os << "AstrumDoubleVector2(" << p.X << ", " << p.Y << ")";
    return os;
}