#pragma once
#include <cmath>
#include <algorithm>

#if defined(__SSE__) || defined(__SSE2__)
#define ASTRUM_USE_SSE 1
#include <immintrin.h>
#else
#define ASTRUM_USE_SSE 0
#endif

struct AstrumVector4 {
#if ASTRUM_USE_SSE
    union {
        struct { float X, Y, Z, W; };
        __m128 m128;
    };
    AstrumVector4(__m128 vec) : m128(vec) { }
    static consteval bool UseSSE() { return true; }
#else
    float X{ 0.0f }, Y{ 0.0f }, Z{ 0.0f }, W{ 0.0f };
    static consteval bool UseSSE() { return false; }
#endif

    AstrumVector4() = default;
    constexpr AstrumVector4(float x, float y, float z, float w = 0.0f) : X(x), Y(y), Z(z), W(w) { }

    float Magnitude() const {
        return std::sqrt(X * X + Y * Y + Z * Z + W * W);
    }
    AstrumVector4 Normalize() const {
        float magnitude = Magnitude();
        if (magnitude == 0.0f) return { 0.0f, 0.0f, 0.0f, 0.0f };
#if ASTRUM_USE_SSE
        return AstrumVector4(_mm_div_ps(m128, _mm_set1_ps(magnitude)));
#else
        return { X / magnitude, Y / magnitude, Z / magnitude, W / magnitude };
#endif
    }
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
    constexpr float Dot(const AstrumVector4& other) const { return X * other.X + Y * other.Y + Z * other.Z + W * other.W; }

    static const AstrumVector4 Origin;

    constexpr AstrumVector4 operator+(const AstrumVector4& v) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_add_ps(m128, v.m128));
        }
#endif
        return { X + v.X, Y + v.Y, Z + v.Z, W + v.W };
    }
    constexpr AstrumVector4 operator-(const AstrumVector4& v) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_sub_ps(m128, v.m128));
        }
#endif
        return { X - v.X, Y - v.Y, Z - v.Z, W - v.W };
    }
    constexpr AstrumVector4 operator*(float scalar) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_mul_ps(m128, _mm_set1_ps(scalar)));
        }
#endif
        return { X * scalar, Y * scalar, Z * scalar, W * scalar };
    }
    constexpr AstrumVector4 operator/(float scalar) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumVector4(_mm_div_ps(m128, _mm_set1_ps(scalar)));
        }
#endif
        return { X / scalar, Y / scalar, Z / scalar, W / scalar };
    }

    constexpr AstrumVector4& operator+=(const AstrumVector4& v) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_add_ps(m128, v.m128);
            return *this;
        }
#endif
        X += v.X; Y += v.Y; Z += v.Z; W += v.W; return *this;
    }
    constexpr AstrumVector4& operator-=(const AstrumVector4& v) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_sub_ps(m128, v.m128);
            return *this;
        }
#endif
        X -= v.X; Y -= v.Y; Z -= v.Z; W -= v.W; return *this;
    }
    constexpr AstrumVector4& operator*=(float scalar) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_mul_ps(m128, _mm_set1_ps(scalar));
            return *this;
        }
#endif
        X *= scalar; Y *= scalar; Z *= scalar; W *= scalar; return *this;
    }
    constexpr AstrumVector4& operator/=(float scalar) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_div_ps(m128, _mm_set1_ps(scalar));
            return *this;
        }
#endif
        X /= scalar; Y /= scalar; Z /= scalar; W /= scalar; return *this;
    }

    constexpr float GetMinimum() const { return (std::min)({ X, Y, Z, W }); }
    constexpr float GetMaximum() const { return (std::max)({ X, Y, Z, W }); }
};

inline constexpr AstrumVector4 AstrumVector4::Origin = { 0.f,0.f,0.f,0.f };

#undef ASTRUM_USE_SSE