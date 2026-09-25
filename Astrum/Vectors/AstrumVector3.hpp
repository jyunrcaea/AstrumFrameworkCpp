#pragma once
#include <iostream>
#include <string>
#include <format>
#include <cmath>
#include <algorithm>
#include "AstrumVector4.hpp"

/// <summary>
/// 3D 벡터를 나타내는 구조체입니다. (float 타입)
/// </summary>
struct AstrumVector3 {
    /// <summary>
    /// 벡터의 X 성분입니다.
    /// </summary>
    float X{ 0.0f }, 
    /// <summary>
    /// 벡터의 Y 성분입니다.
    /// </summary>
    Y{ 0.0f }, 
    /// <summary>
    /// 벡터의 Z 성분입니다.
    /// </summary>
    Z{ 0.0f };

    /// <summary>
    /// 기본 생성자입니다. (0, 0, 0)으로 초기화됩니다.
    /// </summary>
    constexpr AstrumVector3() = default;
    /// <summary>
    /// 지정된 X, Y, Z 값으로 벡터를 생성합니다.
    /// </summary>
    /// <param name="x">X 성분입니다.</param>
    /// <param name="y">Y 성분입니다.</param>
    /// <param name="z">Z 성분입니다. 기본값은 0입니다.</param>
    constexpr AstrumVector3(float x, float y, float z = 0) noexcept : X(x), Y(y), Z(z) { }

    /// <summary>
    /// 벡터의 크기(길이)를 반환합니다.
    /// </summary>
    /// <returns>벡터의 크기입니다.</returns>
    inline float Magnitude() const noexcept { return std::sqrt(X * X + Y * Y + Z * Z); }
    /// <summary>
    /// 정규화된 벡터를 반환합니다. (크기가 1인 벡터)
    /// </summary>
    /// <returns>정규화된 벡터입니다.</returns>
    inline AstrumVector3 Normalize() const noexcept { float mag = Magnitude(); return (mag == 0.0f) ? *this : (*this / mag); }
    /// <summary>
    /// 다른 벡터까지의 거리를 반환합니다.
    /// </summary>
    /// <param name="other">대상 벡터입니다.</param>
    /// <returns>두 벡터 사이의 거리입니다.</returns>
    inline float Distance(const AstrumVector3& other) const noexcept { return std::sqrt((X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y) + (Z - other.Z) * (Z - other.Z)); }
    /// <summary>
    /// 다른 벡터와의 내적(dot product)을 계산합니다.
    /// </summary>
    /// <param name="other">다른 벡터입니다.</param>
    /// <returns>내적 결과입니다.</returns>
    constexpr float Dot(const AstrumVector3& other) const noexcept { return X * other.X + Y * other.Y + Z * other.Z; }
    /// <summary>
    /// 다른 벡터와의 외적(cross product)을 계산합니다.
    /// </summary>
    /// <param name="other">다른 벡터입니다.</param>
    /// <returns>외적 결과 벡터입니다.</returns>
    constexpr AstrumVector3 Cross(const AstrumVector3& other) const noexcept { return { Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X }; }

    /// <summary>
    /// 두 벡터를 더합니다.
    /// </summary>
    constexpr AstrumVector3 operator+(const AstrumVector3& v) const noexcept { return { X + v.X, Y + v.Y, Z + v.Z }; }
    /// <summary>
    /// 한 벡터에서 다른 벡터를 뺍니다.
    /// </summary>
    constexpr AstrumVector3 operator-(const AstrumVector3& v) const noexcept { return { X - v.X, Y - v.Y, Z - v.Z }; }
    /// <summary>
    /// 벡터에 스칼라값을 곱합니다.
    /// </summary>
    constexpr AstrumVector3 operator*(float scalar) const noexcept { return { X * scalar, Y * scalar, Z * scalar }; }
    /// <summary>
    /// 벡터를 스칼라값으로 나눕니다.
    /// </summary>
    constexpr AstrumVector3 operator/(float scalar) const noexcept { return { X / scalar, Y / scalar, Z / scalar }; }

    /// <summary>
    /// 두 벡터의 성분별 곱셈을 합니다.
    /// </summary>
    constexpr AstrumVector3 operator*(const AstrumVector3& v) const noexcept { return { X * v.X, Y * v.Y, Z * v.Z }; }
    /// <summary>
    /// 두 벡터의 성분별 나눗셈을 합니다.
    /// </summary>
    constexpr AstrumVector3 operator/(const AstrumVector3& v) const noexcept { return { X / v.X, Y / v.Y, Z / v.Z }; }

    /// <summary>
    /// 다른 벡터를 더합니다. (복합 할당)
    /// </summary>
    inline AstrumVector3& operator+=(const AstrumVector3& v) noexcept { X += v.X; Y += v.Y; Z += v.Z; return *this; }
    /// <summary>
    /// 다른 벡터를 뺍니다. (복합 할당)
    /// </summary>
    inline AstrumVector3& operator-=(const AstrumVector3& v) noexcept { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// </summary>
    inline AstrumVector3& operator*=(float scalar) noexcept { X *= scalar; Y *= scalar; Z *= scalar; return *this; }
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// </summary>
    inline AstrumVector3& operator/=(float scalar) noexcept { X /= scalar; Y /= scalar; Z /= scalar; return *this; }

    /// <summary>
    /// 벡터의 최소 성분을 반환합니다.
    /// </summary>
    /// <returns>X, Y, Z 중 가장 작은 값입니다.</returns>
    constexpr inline float GetMinimum() const noexcept { return (std::min)((std::min)(X,Y), Z); }
    /// <summary>
    /// 벡터의 최대 성분을 반환합니다.
    /// </summary>
    /// <returns>X, Y, Z 중 가장 큰 값입니다.</returns>
    constexpr inline float GetMaximum() const noexcept { return (std::max)((std::max)(X, Y), Z); }

    /// <summary>
    /// AstrumVector4에서 변환하여 벡터를 생성합니다. (W 좌표 무시)
    /// </summary>
    /// <param name="vec">변환할 4D 벡터입니다.</param>
    explicit AstrumVector3(const struct AstrumVector4& vec) : X(vec.X), Y(vec.Y), Z(vec.Z) {}
    /// <summary>
    /// AstrumVector4로 변환합니다. (W는 0)
    /// </summary>
    operator AstrumVector4() const { return { X, Y, Z, 0.f }; }

    /// <summary>
    /// 원점 (0, 0, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Origin;
    /// <summary>
    /// 전진 방향 (0, 0, 1) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Forward;
    /// <summary>
    /// 후진 방향 (0, 0, -1) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Backward;
    /// <summary>
    /// 위쪽 방향 (0, 1, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Up;
    /// <summary>
    /// 아래쪽 방향 (0, -1, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Down;
    /// <summary>
    /// 왼쪽 방향 (-1, 0, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Left;
    /// <summary>
    /// 오른쪽 방향 (1, 0, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector3 Right;

    /// <summary>
    /// 벡터를 문자열로 표현합니다.
    /// </summary>
    /// <returns>"AstrumVector3(X,Y,Z)" 형식의 문자열입니다.</returns>
	std::string ToString() const { return std::format("AstrumVector3({},{},{})", X, Y, Z); }
};

inline constexpr AstrumVector3 AstrumVector3::Origin = AstrumVector3(0.0f, 0.0f, 0.0f);
inline constexpr AstrumVector3 AstrumVector3::Forward = AstrumVector3(0.0f, 0.0f, 1.0f);
inline constexpr AstrumVector3 AstrumVector3::Backward = AstrumVector3(0.0f, 0.0f, -1.0f);
inline constexpr AstrumVector3 AstrumVector3::Up = AstrumVector3(0.0f, 1.0f, 0.0f);
inline constexpr AstrumVector3 AstrumVector3::Down = AstrumVector3(0.0f, -1.0f, 0.0f);
inline constexpr AstrumVector3 AstrumVector3::Left = AstrumVector3(-1.0f, 0.0f, 0.0f);
inline constexpr AstrumVector3 AstrumVector3::Right = AstrumVector3(1.0f, 0.0f, 0.0f);

namespace {
    std::ostream& operator<<(std::ostream& os, const AstrumVector3& vec) {
        os << vec.ToString();
        return os;
	}
}