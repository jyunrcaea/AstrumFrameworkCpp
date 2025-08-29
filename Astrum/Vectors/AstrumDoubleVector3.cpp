#pragma once
#include <cmath>
#include <algorithm>
#include "AstrumVector4.hpp"

struct AstrumDoubleVector3 {
    double X{ 0.0 }, Y{ 0.0 }, Z{ 0.0 };

    constexpr AstrumDoubleVector3() = default;
    constexpr AstrumDoubleVector3(double x, double y, double z = 0) noexcept : X(x), Y(y), Z(z) { }

    const double Magnitude() const noexcept { return std::sqrt(X * X + Y * Y + Z * Z); }
    const AstrumDoubleVector3 Normalize() const noexcept { double mag = Magnitude(); return (mag == 0.0) ? *this : (*this / mag); }
    const double Distance(const AstrumDoubleVector3& other) const noexcept { return std::sqrt((X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y) + (Z - other.Z) * (Z - other.Z)); }
    constexpr double Dot(const AstrumDoubleVector3& other) const noexcept { return X * other.X + Y * other.Y + Z * other.Z; }
    constexpr AstrumDoubleVector3 Cross(const AstrumDoubleVector3& other) const noexcept { return { Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X }; }

    constexpr AstrumDoubleVector3 operator+(const AstrumDoubleVector3& v) const noexcept { return { X + v.X, Y + v.Y, Z + v.Z }; }
    constexpr AstrumDoubleVector3 operator-(const AstrumDoubleVector3& v) const noexcept { return { X - v.X, Y - v.Y, Z - v.Z }; }
    constexpr AstrumDoubleVector3 operator*(double scalar) const noexcept { return { X * scalar, Y * scalar, Z * scalar }; }
    constexpr AstrumDoubleVector3 operator/(double scalar) const noexcept { return { X / scalar, Y / scalar, Z / scalar }; }

    constexpr AstrumDoubleVector3 operator*(const AstrumDoubleVector3& v) const noexcept { return { X * v.X, Y * v.Y, Z * v.Z }; }
    constexpr AstrumDoubleVector3 operator/(const AstrumDoubleVector3& v) const noexcept { return { X / v.X, Y / v.Y, Z / v.Z }; }

    inline AstrumDoubleVector3& operator+=(const AstrumDoubleVector3& v) noexcept { X += v.X; Y += v.Y; Z += v.Z; return *this; }
    inline AstrumDoubleVector3& operator-=(const AstrumDoubleVector3& v) noexcept { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
    inline AstrumDoubleVector3& operator*=(double scalar) noexcept { X *= scalar; Y *= scalar; Z *= scalar; return *this; }
    inline AstrumDoubleVector3& operator/=(double scalar) noexcept { X /= scalar; Y /= scalar; Z /= scalar; return *this; }

    inline AstrumDoubleVector3& operator*=(const AstrumDoubleVector3& v) noexcept { X *= v.X; Y *= v.Y; Z *= v.Z; return *this; }
    inline AstrumDoubleVector3& operator/=(const AstrumDoubleVector3& v) noexcept { X /= v.X; Y /= v.Y; Z /= v.Z; return *this; }

    constexpr bool operator==(const AstrumDoubleVector3& o) const noexcept { return X == o.X && Y == o.Y && Z == o.Z; }
    constexpr bool operator!=(const AstrumDoubleVector3& o) const noexcept { return !(*this == o); }

    static const AstrumDoubleVector3 Origin;
    static const AstrumDoubleVector3 Forward;
    static const AstrumDoubleVector3 Backward;
    static const AstrumDoubleVector3 Up;
    static const AstrumDoubleVector3 Down;
    static const AstrumDoubleVector3 Left;
    static const AstrumDoubleVector3 Right;
};

inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Origin = AstrumDoubleVector3(0.0, 0.0, 0.0);
inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Forward = AstrumDoubleVector3(0.0, 0.0, 1.0);
inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Backward = AstrumDoubleVector3(0.0, 0.0, -1.0);
inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Up = AstrumDoubleVector3(0.0, 1.0, 0.0);
inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Down = AstrumDoubleVector3(0.0, -1.0, 0.0);
inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Left = AstrumDoubleVector3(-1.0, 0.0, 0.0);
inline constexpr AstrumDoubleVector3 AstrumDoubleVector3::Right = AstrumDoubleVector3(1.0, 0.0, 0.0);
