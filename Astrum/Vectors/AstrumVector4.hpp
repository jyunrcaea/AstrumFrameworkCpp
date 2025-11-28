#pragma once
#include <cmath>
#include <algorithm>

#if defined(__SSE__) || defined(__SSE2__)
#define ASTRUM_USE_SSE 1
#include <immintrin.h>
#else
#define ASTRUM_USE_SSE 0
#endif

/// <summary>
/// 4D 벡터를 나타내는 구조체입니다. (float 타입)
/// SSE 명령어를 지원하는 경우 SIMD 최적화를 사용합니다.
/// </summary>
struct AstrumVector4 {
#if ASTRUM_USE_SSE
    /// <summary>
    /// SSE 지원 시 공용체로 정의됩니다. 벡터 성분 또는 128비트 SIMD 레지스터로 접근 가능합니다.
    /// </summary>
    union {
        struct { 
            /// <summary>
            /// 벡터의 X 성분입니다.
            /// </summary>
            float X;
            /// <summary>
            /// 벡터의 Y 성분입니다.
            /// </summary>
            float Y;
            /// <summary>
            /// 벡터의 Z 성분입니다.
            /// </summary>
            float Z;
            /// <summary>
            /// 벡터의 W 성분입니다.
            /// </summary>
            float W;
        };
        __m128 m128;
    };
    /// <summary>
    /// SSE 128비트 레지스터로부터 벡터를 생성합니다.
    /// </summary>
    /// <param name="vec">SSE 레지스터입니다.</param>
    AstrumVector4(__m128 vec) : m128(vec) { }
    /// <summary>
    /// SSE 명령어 사용 여부를 반환합니다.
    /// </summary>
    /// <returns>SSE 지원 시 true입니다.</returns>
    static consteval bool UseSSE() { return true; }
#else
    /// <summary>
    /// 벡터의 X 성분입니다. 기본값은 0.0f입니다.
    /// </summary>
    float X{ 0.0f };
    /// <summary>
    /// 벡터의 Y 성분입니다. 기본값은 0.0f입니다.
    /// </summary>
    float Y{ 0.0f };
    /// <summary>
    /// 벡터의 Z 성분입니다. 기본값은 0.0f입니다.
    /// </summary>
    float Z{ 0.0f };
    /// <summary>
    /// 벡터의 W 성분입니다. 기본값은 0.0f입니다.
    /// </summary>
    float W{ 0.0f };
    /// <summary>
    /// SSE 명령어 사용 여부를 반환합니다.
    /// </summary>
    /// <returns>SSE 미지원이므로 false입니다.</returns>
    static consteval bool UseSSE() { return false; }
#endif

    /// <summary>
    /// 기본 생성자입니다. (0, 0, 0, 0)으로 초기화됩니다.
    /// </summary>
    AstrumVector4() = default;
    /// <summary>
    /// 지정된 X, Y, Z, W 값으로 벡터를 생성합니다.
    /// </summary>
    /// <param name="x">X 성분입니다.</param>
    /// <param name="y">Y 성분입니다.</param>
    /// <param name="z">Z 성분입니다.</param>
    /// <param name="w">W 성분입니다. 기본값은 0.0f입니다.</param>
    constexpr AstrumVector4(float x, float y, float z, float w = 0.0f) : X(x), Y(y), Z(z), W(w) { }

    /// <summary>
    /// 벡터의 크기(길이)를 반환합니다.
    /// </summary>
    /// <returns>벡터의 크기입니다.</returns>
    float Magnitude() const {
        return std::sqrt(X * X + Y * Y + Z * Z + W * W);
    }
    /// <summary>
    /// 정규화된 벡터를 반환합니다. (크기가 1인 벡터)
    /// </summary>
    /// <returns>정규화된 벡터입니다.</returns>
    AstrumVector4 Normalize() const {
        float magnitude = Magnitude();
        if (magnitude == 0.0f) return { 0.0f, 0.0f, 0.0f, 0.0f };
#if ASTRUM_USE_SSE
        return AstrumVector4(_mm_div_ps(m128, _mm_set1_ps(magnitude)));
#else
        return { X / magnitude, Y / magnitude, Z / magnitude, W / magnitude };
#endif
    }
    /// <summary>
    /// 다른 벡터까지의 거리를 반환합니다.
    /// </summary>
    /// <param name="other">대상 벡터입니다.</param>
    /// <returns>두 벡터 사이의 거리입니다.</returns>
    float Distance(const AstrumVector4& other) const {
#if ASTRUM_USE_SSE
        __m128 diff = _mm_sub_ps(m128, other.m128);
        __m128 squared = _mm_mul_ps(diff, diff);
        __m128 temp = _mm_hadd_ps(squared, squared);
        temp = _mm_hadd_ps(temp, temp);
        return _mm_cvtss_f32(_mm_sqrt_ss(temp));
#else
        return std::sqrt((X - other.X) * (X - other.X) +
            (Y - other.Y) * (Y - other.Y) +
            (Z - other.Z) * (Z - other.Z) +
            (W - other.W) * (W - other.W));
#endif
    }
    /// <summary>
    /// 다른 벡터와의 내적(dot product)을 계산합니다.
    /// </summary>
    /// <param name="other">다른 벡터입니다.</param>
    /// <returns>내적 기출입니다.</returns>
    constexpr float Dot(const AstrumVector4& other) const { return X * other.X + Y * other.Y + Z * other.Z + W * other.W; }

    /// <summary>
    /// 원점 (0, 0, 0, 0) 벡터입니다.
    /// </summary>
    static const AstrumVector4 Origin;

    /// <summary>
    /// 두 벡터를 더합니다.
    /// </summary>
    constexpr AstrumVector4 operator+(const AstrumVector4& v) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_add_ps(m128, v.m128));
        }
#endif
        return { X + v.X, Y + v.Y, Z + v.Z, W + v.W };
    }
    /// <summary>
    /// 한 벡터에서 다른 벡터를 뺍니다.
    /// </summary>
    constexpr AstrumVector4 operator-(const AstrumVector4& v) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_sub_ps(m128, v.m128));
        }
#endif
        return { X - v.X, Y - v.Y, Z - v.Z, W - v.W };
    }
    /// <summary>
    /// 벡터에 스칼라값을 곱합니다.
    /// </summary>
    constexpr AstrumVector4 operator*(float scalar) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_mul_ps(m128, _mm_set1_ps(scalar)));
        }
#endif
        return { X * scalar, Y * scalar, Z * scalar, W * scalar };
    }
    /// <summary>
    /// 벡터를 스칼라값으로 나눕니다.
    /// </summary>
    constexpr AstrumVector4 operator/(float scalar) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_div_ps(m128, _mm_set1_ps(scalar)));
        }
#endif
        return { X / scalar, Y / scalar, Z / scalar, W / scalar };
    }

    /// <summary>
    /// 다른 벡터를 더합니다. (복합 할당)
    /// </summary>
    constexpr AstrumVector4& operator+=(const AstrumVector4& v) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_add_ps(m128, v.m128);
            return *this;
        }
#endif
        X += v.X; Y += v.Y; Z += v.Z; W += v.W; return *this;
    }
    /// <summary>
    /// 다른 벡터를 뺍니다. (복합 할당)
    /// </summary>
    constexpr AstrumVector4& operator-=(const AstrumVector4& v) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_sub_ps(m128, v.m128);
            return *this;
        }
#endif
        X -= v.X; Y -= v.Y; Z -= v.Z; W -= v.W; return *this;
    }
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// </summary>
    constexpr AstrumVector4& operator*=(float scalar) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_mul_ps(m128, _mm_set1_ps(scalar));
            return *this;
        }
#endif
        X *= scalar; Y *= scalar; Z *= scalar; W *= scalar; return *this;
    }
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// </summary>
    constexpr AstrumVector4& operator/=(float scalar) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_div_ps(m128, _mm_set1_ps(scalar));
            return *this;
        }
#endif
        X /= scalar; Y /= scalar; Z /= scalar; W /= scalar; return *this;
    }

    /// <summary>
    /// 벡터의 최소 성분을 반환합니다.
    /// </summary>
    /// <returns>X, Y, Z, W 중 가장 작은 값입니다.</returns>
    constexpr float GetMinimum() const { return (std::min)({ X, Y, Z, W }); }
    /// <summary>
    /// 벡터의 최대 성분을 반환합니다.
    /// </summary>
    /// <returns>X, Y, Z, W 중 가장 큰 값입니다.</returns>
    constexpr float GetMaximum() const { return (std::max)({ X, Y, Z, W }); }
};

inline constexpr AstrumVector4 AstrumVector4::Origin = { 0.f,0.f,0.f,0.f };

#undef ASTRUM_USE_SSE