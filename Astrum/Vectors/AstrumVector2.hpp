#pragma once
#include <string>
#include <format>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "AstrumVector3.hpp"
#include "AstrumDoubleVector2.hpp"

/// <summary>
/// 2D 벡터를 나타내는 구조체입니다. (float 타입)
/// </summary>
struct AstrumVector2 {
    /// <summary>
    /// 벡터의 X 성분입니다.
    /// </summary>
    float X = 0.0f;
    /// <summary>
    /// 벡터의 Y 성분입니다.
    /// </summary>
    float Y = 0.0f;

    /// <summary>
    /// 기본 생성자입니다. (0, 0)으로 초기화됩니다.
    /// </summary>
    constexpr AstrumVector2() = default;
    /// <summary>
    /// 지정된 X, Y 값으로 벡터를 생성합니다.
    /// </summary>
    /// <param name="x">X 성분입니다.</param>
    /// <param name="y">Y 성분입니다.</param>
    constexpr AstrumVector2(float x, float y) noexcept : X(x), Y(y) {};

    /// <summary>
    /// 벡터의 크기(길이)를 반환합니다.
    /// </summary>
    /// <returns>벡터의 크기입니다.</returns>
    float Magnitude() const { return std::sqrt(X * X + Y * Y); }
    /// <summary>
    /// 정규화된 벡터를 반환합니다. (크기가 1인 벡터)
    /// </summary>
    /// <returns>정규화된 벡터입니다.</returns>
    AstrumVector2 Normalize() const { float mag = Magnitude(); return (mag == 0.0f) ? *this : (*this / mag); }
    /// <summary>
    /// 다른 벡터까지의 거리를 반환합니다.
    /// </summary>
    /// <param name="other">대상 벡터입니다.</param>
    /// <returns>두 벡터 사이의 거리입니다.</returns>
    float Distance(const AstrumVector2& other) const { return std::sqrt((X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y)); }
    /// <summary>
    /// 다른 벡터와의 내적(dot product)을 계산합니다.
    /// </summary>
    /// <param name="other">다른 벡터입니다.</param>
    /// <returns>내적 결과입니다.</returns>
    constexpr float Dot(const AstrumVector2& other) const noexcept { return X * other.X + Y * other.Y; }
    /// <summary>
    /// 지정된 중심점을 기준으로 벡터를 회전시킵니다.
    /// </summary>
    /// <param name="pivot">회전 중심점입니다.</param>
    /// <param name="rotation">회전 각도(도)입니다.</param>
    /// <returns>회전된 벡터입니다.</returns>
    AstrumVector2 Rotate(AstrumVector2 pivot, float rotation) const {
        const float rad = rotation * 3.14159265f / 180.f;
        const float c = cosf(rad), s = sinf(rad);
        const float dx = X - pivot.X, dy = Y - pivot.Y;
        return {
            pivot.X + dx * c - dy * s,
            pivot.Y + dx * s + dy * c
        };
    }
    
    /// <summary>
    /// 두 벡터를 더합니다.
    /// </summary>
    constexpr AstrumVector2 operator+(const AstrumVector2& v) const noexcept { return { X + v.X, Y + v.Y }; }
    /// <summary>
    /// 한 벡터에서 다른 벡터를 뺍니다.
    /// </summary>
    constexpr AstrumVector2 operator-(const AstrumVector2& v) const noexcept { return { X - v.X, Y - v.Y }; }
    /// <summary>
    /// 두 벡터의 성분별 곱셈을 합니다.
    /// </summary>
    constexpr AstrumVector2 operator*(const AstrumVector2& v) const noexcept { return { X * v.X, Y * v.Y }; }
    /// <summary>
    /// 두 벡터의 성분별 나눗셈을 합니다.
    /// </summary>
    constexpr AstrumVector2 operator/(const AstrumVector2& v) const noexcept { return { X / v.X, Y / v.Y }; }
    /// <summary>
    /// 벡터에 스칼라값을 곱합니다.
    /// </summary>
    constexpr AstrumVector2 operator*(float scalar) const noexcept { return { X * scalar, Y * scalar }; }
    /// <summary>
    /// 벡터를 스칼라값으로 나눕니다.
    /// </summary>
    constexpr AstrumVector2 operator/(float scalar) const noexcept { return { X / scalar, Y / scalar }; }

    /// <summary>
    /// 두 벡터가 같은지 비교합니다.
    /// </summary>
	constexpr bool operator==(const AstrumVector2& v) const noexcept { return X == v.X && Y == v.Y; }
    /// <summary>
    /// 두 벡터가 다른지 비교합니다.
    /// </summary>
	constexpr bool operator!=(const AstrumVector2& v) const noexcept { return !(*this == v); }
    
    /// <summary>
    /// 다른 벡터를 더합니다. (복합 할당)
    /// </summary>
    AstrumVector2& operator+=(const AstrumVector2& v) noexcept { X += v.X; Y += v.Y; return *this; }
    /// <summary>
    /// 다른 벡터를 뺍니다. (복합 할당)
    /// </summary>
    AstrumVector2& operator-=(const AstrumVector2& v) noexcept { X -= v.X; Y -= v.Y; return *this; }
    /// <summary>
    /// 다른 벡터와 성분별 곱셈을 합니다. (복합 할당)
    /// </summary>
    AstrumVector2& operator*=(const AstrumVector2& v) noexcept { X *= v.X; Y *= v.Y; return *this; }
    /// <summary>
    /// 다른 벡터와 성분별 나눗셈을 합니다. (복합 할당)
    /// </summary>
    AstrumVector2& operator/=(const AstrumVector2& v) noexcept { X /= v.X; Y /= v.Y; return *this; }
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// </summary>
    AstrumVector2& operator*=(float scalar) noexcept { X *= scalar; Y *= scalar; return *this; }
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// </summary>
    AstrumVector2& operator/=(float scalar) noexcept { X /= scalar; Y /= scalar; return *this; }
    
    /// <summary>
    /// 벡터의 최소 성분을 반환합니다.
    /// </summary>
    /// <returns>X와 Y 중 작은 값입니다.</returns>
    constexpr inline float GetMinimum() const noexcept { return (std::min)(X, Y); }
    /// <summary>
    /// 벡터의 최대 성분을 반환합니다.
    /// </summary>
    /// <returns>X와 Y 중 큰 값입니다.</returns>
    constexpr inline float GetMaximum() const noexcept { return (std::max)(X, Y); }
    
    /// <summary>
    /// AstrumVector3에서 변환하여 벡터를 생성합니다. (Z 좌표 무시)
    /// </summary>
    /// <param name="vec3">변환할 3D 벡터입니다.</param>
    explicit AstrumVector2(const struct AstrumVector3& vec3) noexcept : X(vec3.X), Y(vec3.Y) {}
    /// <summary>
    /// AstrumDoubleVector2에서 변환하여 벡터를 생성합니다.
    /// </summary>
    /// <param name="vecd2">변환할 double 2D 벡터입니다.</param>
    explicit AstrumVector2(const struct AstrumDoubleVector2& vecd2) noexcept : X(static_cast<float>(vecd2.X)), Y(static_cast<float>(vecd2.Y)) {}
    /// <summary>
    /// AstrumVector3으로 변환합니다. (Z는 0)
    /// </summary>
    operator AstrumVector3() { return { X, Y, 0 }; }
    /// <summary>
    /// AstrumDoubleVector2로 변환합니다.
    /// </summary>
	operator AstrumDoubleVector2() { return { static_cast<double>(X), static_cast<double>(Y) }; }
    /// <summary>
    /// 지정된 Z 값으로 AstrumVector3로 변환합니다.
    /// </summary>
    /// <param name="z">생성할 3D 벡터의 Z 값입니다. 기본값은 0입니다.</param>
    /// <returns>변환된 3D 벡터입니다.</returns>
    struct AstrumVector3 ToVector3(float z = 0) const noexcept { return { X,Y,z }; }
    /// <summary>
    /// 벡터를 문자열로 표현합니다.
    /// </summary>
    /// <returns>"AstrumVector2(X,Y)" 형식의 문자열입니다.</returns>
    std::string ToString() const { return std::format("AstrumVector2({},{})",X,Y); }
    
    /// <summary>
    /// 원점 (0, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector2 Origin;
};

inline constexpr AstrumVector2 AstrumVector2::Origin = AstrumVector2(0.0f, 0.0f);

namespace {
    std::ostream& operator<<(std::ostream& os, const AstrumVector2& p) {
        os << "AstrumVector2(" << p.X << ", " << p.Y << ")";
        return os;
    }
}