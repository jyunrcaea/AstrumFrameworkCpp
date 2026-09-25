#pragma once
#include <cmath>
#include <cstddef>
#include <algorithm>

// SSE2 사용 여부. (GCC/Clang은 __SSE2__, MSVC는 x64 또는 /arch:SSE2 이상일 때 _M_X64/_M_IX86_FP로 확인)
// 다른 헤더가 같은 이름의 매크로를 쓰더라도 영향을 주지 않도록 push/pop 합니다.
#pragma push_macro("ASTRUM_USE_SSE")
#undef ASTRUM_USE_SSE
#if defined(__SSE2__) || defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
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
#if ASTRUM_USE_SSE
    // 메모리 배치는 SSE 사용 여부와 관계없이 float 4개(16바이트, 4바이트 정렬)로 동일하게 유지합니다.
    // (상수 버퍼/정점 구조체의 배치가 바뀌지 않도록 __m128 멤버나 공용체를 두지 않고, 연산할 때만 읽고 씁니다.)
    /// <summary>
    /// SSE 128비트 레지스터로부터 벡터를 생성합니다.
    /// </summary>
    /// <param name="vec">SSE 레지스터입니다.</param>
    AstrumVector4(__m128 vec) { Store(vec); }
    /// <summary>
    /// 벡터를 SSE 128비트 레지스터로 읽어옵니다.
    /// </summary>
    __m128 Load() const { return _mm_loadu_ps(&X); }
    /// <summary>
    /// SSE 128비트 레지스터의 값을 벡터에 씁니다.
    /// </summary>
    void Store(__m128 vec) { _mm_storeu_ps(&X, vec); }
    /// <summary>
    /// SSE 명령어 사용 여부를 반환합니다.
    /// </summary>
    /// <returns>SSE 지원 시 true입니다.</returns>
    static consteval bool UseSSE() { return true; }
#else
    /// <summary>
    /// SSE 명령어 사용 여부를 반환합니다.
    /// </summary>
    /// <returns>SSE 지원 시 true입니다.</returns>
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
        return AstrumVector4(_mm_div_ps(Load(), _mm_set1_ps(magnitude)));
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
        __m128 diff = _mm_sub_ps(Load(), other.Load());
        __m128 squared = _mm_mul_ps(diff, diff);
        // SSE2만으로 네 성분을 더합니다. (_mm_hadd_ps는 SSE3 명령어)
        __m128 shuffled = _mm_shuffle_ps(squared, squared, _MM_SHUFFLE(2, 3, 0, 1)); // (y, x, w, z)
        __m128 sums = _mm_add_ps(squared, shuffled);                                  // (x+y, x+y, z+w, z+w)
        shuffled = _mm_movehl_ps(shuffled, sums);                                     // (z+w, z+w, ...)
        sums = _mm_add_ss(sums, shuffled);                                            // (x+y+z+w, ...)
        return _mm_cvtss_f32(_mm_sqrt_ss(sums));
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
            return AstrumVector4(_mm_add_ps(Load(), v.Load()));
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
            return AstrumVector4(_mm_sub_ps(Load(), v.Load()));
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
            return AstrumVector4(_mm_mul_ps(Load(), _mm_set1_ps(scalar)));
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
            return AstrumVector4(_mm_div_ps(Load(), _mm_set1_ps(scalar)));
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
            Store(_mm_add_ps(Load(), v.Load()));
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
            Store(_mm_sub_ps(Load(), v.Load()));
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
            Store(_mm_mul_ps(Load(), _mm_set1_ps(scalar)));
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
            Store(_mm_div_ps(Load(), _mm_set1_ps(scalar)));
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

// SSE 연산은 X부터 연속된 float 4개를 읽고 쓰므로, 패딩 없이 16바이트로 배치되어야 합니다.
static_assert(sizeof(AstrumVector4) == sizeof(float) * 4 && offsetof(AstrumVector4, W) == sizeof(float) * 3);

inline constexpr AstrumVector4 AstrumVector4::Origin = { 0.f,0.f,0.f,0.f };

#pragma pop_macro("ASTRUM_USE_SSE")
