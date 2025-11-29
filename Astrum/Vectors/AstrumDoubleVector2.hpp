#pragma once
#include <string>
#include <format>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numbers>
#include <type_traits>
#include <utility>

#if defined(__SSE__) || defined(__SSE2__)
#define ASTRUM_USE_SSE 1
#include <immintrin.h>
#else
#define ASTRUM_USE_SSE 0
#endif

/// <summary>
/// 2D 벡터를 나타내는 구조체입니다. (double 타입)
/// AstrumVector2의 고정밀 버전으로, 더 높은 정밀도가 필요할 때 사용됩니다.
/// </summary>
struct AstrumDoubleVector2 {
    /// <summary>
    /// 벡터의 X 성분입니다.
    /// </summary>
    double X = 0.0;
    /// <summary>
    /// 벡터의 Y 성분입니다.
    /// </summary>
    double Y = 0.0;

#if ASTRUM_USE_SSE
    // Helpers to construct/load SSE registers from X/Y without storing an __m128d as active union member
    inline __m128d mm() const noexcept { return _mm_setr_pd(X, Y); }
    static inline AstrumDoubleVector2 from_mm(__m128d m) noexcept {
        double tmp[2]; _mm_storeu_pd(tmp, m); return { tmp[0], tmp[1] };
    }
#endif

    /// <summary>
    /// 기본 생성자입니다. (0, 0)으로 초기화됩니다.
    /// </summary>
    constexpr AstrumDoubleVector2() = default;
    /// <summary>
    /// 지정된 X, Y 값으로 벡터를 생성합니다.
    /// </summary>
    /// <param name="x">X 성분입니다.</param>
    /// <param name="y">Y 성분입니다.</param>
    constexpr AstrumDoubleVector2(double x, double y) noexcept : X(x), Y(y) {}

// __m128d constructor intentionally omitted to keep double constructor constexpr and avoid inactive-union reads

    /// <summary>
    /// 벡터의 크기(길이)를 반환합니다.
    /// </summary>
    /// <returns>벡터의 크기입니다.</returns>
    double Magnitude() const noexcept { return std::sqrt(X * X + Y * Y); }
    /// <summary>
    /// 정규화된 벡터를 반환합니다. (크기가 1인 벡터)
    /// </summary>
    /// <returns>정규화된 벡터입니다.</returns>
    AstrumDoubleVector2 Normalize() const noexcept {
        const double mag = Magnitude();
        return (mag == 0.0) ? *this : (*this / mag);
    }
    /// <summary>
    /// 다른 벡터까지의 거리를 반환합니다.
    /// </summary>
    /// <param name="other">대상 벡터입니다.</param>
    /// <returns>두 벡터 사이의 거리입니다.</returns>
    double Distance(const AstrumDoubleVector2& other) const noexcept {
        const double dx = X - other.X, dy = Y - other.Y;
        return std::sqrt(dx * dx + dy * dy);
    }
    /// <summary>
    /// 다른 벡터와의 내적(dot product)을 계산합니다.
    /// </summary>
    /// <param name="other">다른 벡터입니다.</param>
    /// <returns>내적 결과입니다.</returns>
    constexpr double Dot(const AstrumDoubleVector2& other) const noexcept { return X * other.X + Y * other.Y; }

    /// <summary>
    /// 지정된 중심점을 기준으로 벡터를 회전시킵니다.
    /// </summary>
    /// <param name="pivot">회전 중심점입니다.</param>
    /// <param name="rotationDegrees">회전 각도(도)입니다.</param>
    /// <returns>회전된 벡터입니다.</returns>
    AstrumDoubleVector2 Rotate(AstrumDoubleVector2 pivot, double rotationDegrees) const noexcept {
        const double rad = rotationDegrees * std::numbers::pi_v<double> / 180.0;
        const double c = std::cos(rad), s = std::sin(rad);
        const double dx = X - pivot.X, dy = Y - pivot.Y;
        return {
            pivot.X + dx * c - dy * s,
            pivot.Y + dx * s + dy * c
        };
    }

    /// <summary>
    /// 두 벡터를 더합니다.
    /// </summary>
    constexpr AstrumDoubleVector2 operator+(const AstrumDoubleVector2& v) const noexcept {
        if (std::is_constant_evaluated()) {
            // Ensure this can be evaluated at compile-time
            return { X + v.X, Y + v.Y };
        }
#if ASTRUM_USE_SSE
        // At runtime prefer SSE path when available
        return from_mm(_mm_add_pd(mm(), v.mm()));
#else
        return { X + v.X, Y + v.Y };
#endif
    }
    /// <summary>
    /// 한 벡터에서 다른 벡터를 뺍니다.
    /// </summary>
    constexpr AstrumDoubleVector2 operator-(const AstrumDoubleVector2& v) const noexcept {
        if (std::is_constant_evaluated()) {
            return { X - v.X, Y - v.Y };
        }
#if ASTRUM_USE_SSE
        return from_mm(_mm_sub_pd(mm(), v.mm()));
#else
        return { X - v.X, Y - v.Y };
#endif
    }
    /// <summary>
    /// 두 벡터의 성분별 곱셈을 합니다.
    /// </summary>
    constexpr AstrumDoubleVector2 operator*(const AstrumDoubleVector2& v) const noexcept {
        if (std::is_constant_evaluated()) {
            return { X * v.X, Y * v.Y };
        }
#if ASTRUM_USE_SSE
        return from_mm(_mm_mul_pd(mm(), v.mm()));
#else
        return { X * v.X, Y * v.Y };
#endif
    }
    /// <summary>
    /// 두 벡터의 성분별 나눗셈을 합니다.
    /// </summary>
    constexpr AstrumDoubleVector2 operator/(const AstrumDoubleVector2& v) const noexcept {
        if (std::is_constant_evaluated()) {
            return { X / v.X, Y / v.Y };
        }
#if ASTRUM_USE_SSE
        return from_mm(_mm_div_pd(mm(), v.mm()));
#else
        return { X / v.X, Y / v.Y };
#endif
    }

    /// <summary>
    /// 벡터에 스칼라값을 곱합니다.
    /// </summary>
    constexpr AstrumDoubleVector2 operator*(double scalar) const noexcept {
        if (std::is_constant_evaluated()) {
            return { X * scalar, Y * scalar };
        }
#if ASTRUM_USE_SSE
        return from_mm(_mm_mul_pd(mm(), _mm_set1_pd(scalar)));
#else
        return { X * scalar, Y * scalar };
#endif
    }
    /// <summary>
    /// 벡터를 스칼라값으로 나눕니다.
    /// </summary>
    constexpr AstrumDoubleVector2 operator/(double scalar) const noexcept {
        if (std::is_constant_evaluated()) {
            return { X / scalar, Y / scalar };
        }
#if ASTRUM_USE_SSE
        return from_mm(_mm_div_pd(mm(), _mm_set1_pd(scalar)));
#else
        return { X / scalar, Y / scalar };
#endif
    }
    /// <summary>
    /// 스칼라값에 벡터를 곱합니다. (left multiplication)
    /// </summary>
    friend constexpr AstrumDoubleVector2 operator*(double scalar, const AstrumDoubleVector2& v) noexcept {
        if (std::is_constant_evaluated()) {
            return { v.X * scalar, v.Y * scalar };
        }
#if ASTRUM_USE_SSE
        return from_mm(_mm_mul_pd(v.mm(), _mm_set1_pd(scalar)));
#else
        return { v.X * scalar, v.Y * scalar };
#endif
    }

    /// <summary>
    /// 다른 벡터를 더합니다. (복합 할당)
    /// </summary>
#if ASTRUM_USE_SSE
    AstrumDoubleVector2& operator+=(const AstrumDoubleVector2& v) noexcept { *this = from_mm(_mm_add_pd(mm(), v.mm())); return *this; }
#else
    AstrumDoubleVector2& operator+=(const AstrumDoubleVector2& v) noexcept { X += v.X; Y += v.Y; return *this; }
#endif
    /// <summary>
    /// 다른 벡터를 뺍니다. (복합 할당)
    /// </summary>
#if ASTRUM_USE_SSE
    AstrumDoubleVector2& operator-=(const AstrumDoubleVector2& v) noexcept { *this = from_mm(_mm_sub_pd(mm(), v.mm())); return *this; }
#else
    AstrumDoubleVector2& operator-=(const AstrumDoubleVector2& v) noexcept { X -= v.X; Y -= v.Y; return *this; }
#endif
    /// <summary>
    /// 다른 벡터와 성분별 곱셈을 합니다. (복합 할당)
    /// </summary>
#if ASTRUM_USE_SSE
    AstrumDoubleVector2& operator*=(const AstrumDoubleVector2& v) noexcept { *this = from_mm(_mm_mul_pd(mm(), v.mm())); return *this; }
#else
    AstrumDoubleVector2& operator*=(const AstrumDoubleVector2& v) noexcept { X *= v.X; Y *= v.Y; return *this; }
#endif
    /// <summary>
    /// 다른 벡터와 성분별 나눗셈을 합니다. (복합 할당)
    /// </summary>
    AstrumDoubleVector2& operator/=(const AstrumDoubleVector2& v) noexcept {
#if ASTRUM_USE_SSE
        *this = from_mm(_mm_div_pd(mm(), v.mm()));
        return *this;
#else
        X /= v.X;
        Y /= v.Y;
        return *this;
#endif
    }
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// </summary>
    AstrumDoubleVector2& operator*=(double scalar) noexcept {
#if ASTRUM_USE_SSE
        *this = from_mm(_mm_mul_pd(mm(), _mm_set1_pd(scalar)));
        return *this;
#else
        X *= scalar;
        Y *= scalar;
        return *this;
#endif
    }
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// </summary>
    AstrumDoubleVector2& operator/=(double scalar) noexcept { 
#if ASTRUM_USE_SSE
        * this = from_mm(_mm_div_pd(mm(), _mm_set1_pd(scalar)));
        return *this;
#else
        X /= scalar;
        Y /= scalar;
        return *this;
#endif
    }

    /// <summary>
    /// 벡터의 최소 성분을 반환합니다.
    /// </summary>
    /// <returns>X와 Y 중 작은 값입니다.</returns>
    constexpr double GetMinimum() const noexcept { return (std::min)(X, Y); }
    /// <summary>
    /// 벡터의 최대 성분을 반환합니다.
    /// </summary>
    /// <returns>X와 Y 중 큰 값입니다.</returns>
    constexpr double GetMaximum() const noexcept { return (std::max)(X, Y); }

    /// <summary>
    /// 원점 (0, 0) 벡터입니다.
    /// </summary>
    static const AstrumDoubleVector2 Origin;
};

inline constexpr AstrumDoubleVector2 AstrumDoubleVector2::Origin = { 0, 0 };

/// <summary>
/// AstrumDoubleVector2를 출력 스트림에 출력합니다.
/// </summary>
/// <param name="os">출력 스트림입니다.</param>
/// <param name="p">출력할 벡터입니다.</param>
/// <returns>출력 스트림 참조입니다.</returns>
inline std::ostream& operator<<(std::ostream& os, const AstrumDoubleVector2& p) {
    os << "AstrumDoubleVector2(" << p.X << ", " << p.Y << ")";
    return os;
}

#undef ASTRUM_USE_SSE