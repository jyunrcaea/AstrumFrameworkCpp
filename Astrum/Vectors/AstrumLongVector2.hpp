#pragma once
#include <string>
#include <format>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numbers>

/// <summary>
/// 2D 벡터를 나타내는 구조체입니다. (long long 정수 타입)
/// 픽셀 좌표, 타일 맵 인덱스 또는 정수 기반의 2D 위치 저장에 사용됩니다.
/// </summary>
struct AstrumLongVector2
{
    /// <summary>
    /// 벡터의 X 성분입니다. (long long 정수)
    /// </summary>
    long long int X = 0;
    /// <summary>
    /// 벡터의 Y 성분입니다. (long long 정수)
    /// </summary>
    long long int Y = 0;

    /// <summary>
    /// 기본 생성자입니다. (0, 0)으로 초기화됩니다.
    /// </summary>
    constexpr AstrumLongVector2() = default;
    /// <summary>
    /// 지정된 X, Y 값으로 벡터를 생성합니다.
    /// </summary>
    /// <param name="x">X 성분입니다. (long long 정수)</param>
    /// <param name="y">Y 성분입니다. (long long 정수)</param>
    constexpr AstrumLongVector2(long long x, long long y) noexcept : X(x), Y(y) {}

    /// <summary>
    /// 벡터의 크기(길이)를 반환합니다.
    /// 정수 벡터이므로 결과는 double로 반환됩니다.
    /// </summary>
    /// <returns>벡터의 크기입니다.</returns>
    double Magnitude() const noexcept { return std::sqrt(X * X + Y * Y); }
    /// <summary>
    /// 다른 벡터까지의 거리를 반환합니다.
    /// </summary>
    /// <param name="other">대상 벡터입니다.</param>
    /// <returns>두 벡터 사이의 거리입니다.</returns>
    double Distance(const AstrumLongVector2& other) const noexcept {
        const long long dx = X - other.X, dy = Y - other.Y;
        return std::sqrt(dx * dx + dy * dy);
    }
    /// <summary>
    /// 다른 벡터와의 내적(dot product)을 계산합니다.
    /// </summary>
    /// <param name="other">다른 벡터입니다.</param>
    /// <returns>내적 결과입니다. (long long 정수)</returns>
    constexpr long long Dot(const AstrumLongVector2& other) const noexcept { return X * other.X + Y * other.Y; }

    /// <summary>
    /// 두 벡터를 더합니다.
    /// </summary>
    constexpr AstrumLongVector2 operator+(const AstrumLongVector2& v) const noexcept { return { X + v.X, Y + v.Y }; }
    /// <summary>
    /// 한 벡터에서 다른 벡터를 뺍니다.
    /// </summary>
    constexpr AstrumLongVector2 operator-(const AstrumLongVector2& v) const noexcept { return { X - v.X, Y - v.Y }; }
    /// <summary>
    /// 두 벡터의 성분별 곱셈을 합니다.
    /// </summary>
    constexpr AstrumLongVector2 operator*(const AstrumLongVector2& v) const noexcept { return { X * v.X, Y * v.Y }; }
    /// <summary>
    /// 두 벡터의 성분별 나눗셈을 합니다.
    /// </summary>
    constexpr AstrumLongVector2 operator/(const AstrumLongVector2& v) const noexcept { return { X / v.X, Y / v.Y }; }

    /// <summary>
    /// 벡터에 정수 스칼라값을 곱합니다.
    /// </summary>
    constexpr AstrumLongVector2 operator*(long long scalar) const noexcept { return { X * scalar, Y * scalar }; }
    /// <summary>
    /// 벡터를 정수 스칼라값으로 나눕니다.
    /// </summary>
    constexpr AstrumLongVector2 operator/(long long scalar) const noexcept { return { X / scalar, Y / scalar }; }
    /// <summary>
    /// 정수 스칼라값에 벡터를 곱합니다. (left multiplication)
    /// </summary>
    friend constexpr AstrumLongVector2 operator*(long long scalar, const AstrumLongVector2& v) noexcept { return { v.X * scalar, v.Y * scalar }; }

    /// <summary>
    /// 다른 벡터를 더합니다. (복합 할당)
    /// </summary>
    AstrumLongVector2& operator+=(const AstrumLongVector2& v) noexcept { X += v.X; Y += v.Y; return *this; }
    /// <summary>
    /// 다른 벡터를 뺍니다. (복합 할당)
    /// </summary>
    AstrumLongVector2& operator-=(const AstrumLongVector2& v) noexcept { X -= v.X; Y -= v.Y; return *this; }
    /// <summary>
    /// 다른 벡터와 성분별 곱셈을 합니다. (복합 할당)
    /// </summary>
    AstrumLongVector2& operator*=(const AstrumLongVector2& v) noexcept { X *= v.X; Y *= v.Y; return *this; }
    /// <summary>
    /// 다른 벡터와 성분별 나눗셈을 합니다. (복합 할당)
    /// </summary>
    AstrumLongVector2& operator/=(const AstrumLongVector2& v) noexcept { X /= v.X; Y /= v.Y; return *this; }
    /// <summary>
    /// 정수 스칼라값을 곱합니다. (복합 할당)
    /// </summary>
    AstrumLongVector2& operator*=(long long scalar) noexcept { X *= scalar; Y *= scalar; return *this; }
    /// <summary>
    /// 정수 스칼라값으로 나눕니다. (복합 할당)
    /// </summary>
    AstrumLongVector2& operator/=(long long scalar) noexcept { X /= scalar; Y /= scalar; return *this; }

    /// <summary>
    /// 벡터의 최소 성분을 반환합니다.
    /// </summary>
    /// <returns>X와 Y 중 작은 값입니다.</returns>
    constexpr long long GetMinimum() const noexcept { return (std::min)(X, Y); }
    /// <summary>
    /// 벡터의 최대 성분을 반환합니다.
    /// </summary>
    /// <returns>X와 Y 중 큰 값입니다.</returns>
    constexpr long long GetMaximum() const noexcept { return (std::max)(X, Y); }

    /// <summary>
    /// 원점 (0, 0) 벡터입니다.
    /// </summary>
    static const AstrumLongVector2 Origin;
};

inline constexpr AstrumLongVector2 AstrumLongVector2::Origin = { 0, 0 };

/// <summary>
/// AstrumLongVector2를 출력 스트림에 출력합니다.
/// </summary>
/// <param name="os">출력 스트림입니다.</param>
/// <param name="p">출력할 벡터입니다.</param>
/// <returns>출력 스트림 참조입니다.</returns>
inline std::ostream& operator<<(std::ostream& os, const AstrumLongVector2& p) {
    os << "AstrumLongVector2(" << p.X << ", " << p.Y << ")";
    return os;
}