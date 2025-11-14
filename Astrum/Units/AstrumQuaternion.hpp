#pragma once
#include <numbers>
#include <cmath>
#include <algorithm> // for std::is_constant_evaluated
#include "../Vectors/AstrumVector3.hpp"

// Vector4와 마찬가지로 SSE 지원 여부를 확인합니다.
#if defined(__SSE__) || defined(__SSE2__)
#define ASTRUM_USE_SSE 1
#include <immintrin.h> // SSE 내장 함수
#else
#define ASTRUM_USE_SSE 0
#endif

namespace {
    // 상수들을 헤더 파일 내에서 사용할 수 있도록 처리
    constexpr float DEG2RAD = static_cast<float>(std::numbers::pi / 180.0);
    constexpr float RAD2DEG = static_cast<float>(180.0 / std::numbers::pi);
}

struct AstrumQuaternion {
#if ASTRUM_USE_SSE
    union {
        struct { float W, X, Y, Z; };
        __m128 m128;
    };
    // SSE 레지스터에서 바로 생성하는 생성자
    AstrumQuaternion(__m128 vec) : m128(vec) {}
#else
    float W, X, Y, Z;
#endif

    // 기본 생성자
    constexpr AstrumQuaternion() : W(0.0f), X(0.0f), Y(0.0f), Z(0.0f) {}
    // 초기화 생성자
    constexpr AstrumQuaternion(float w, float x, float y, float z) : W(w), X(x), Y(y), Z(z) {}

    // --- 정적 함수 (Static Functions) ---

    static inline AstrumQuaternion Identity() {
        // 단위 사원수: 회전이 없음
        return AstrumQuaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
    }

    static inline AstrumQuaternion FromAxisAngle(AstrumVector3 axis, float rad) {
        // 축을 정규화
        AstrumVector3 norm = axis.Normalize();
        float halfAngle = rad * 0.5f;
        float sinHalf = std::sin(halfAngle);
        float cosHalf = std::cos(halfAngle);
        return AstrumQuaternion{ cosHalf, norm.X * sinHalf, norm.Y * sinHalf, norm.Z * sinHalf };
    }

    static inline AstrumQuaternion FromEuler(AstrumVector3 deg) {
        // 오일러 각(degree)을 라디안으로 변환
        float roll = deg.X * DEG2RAD;
        float pitch = deg.Y * DEG2RAD;
        float yaw = deg.Z * DEG2RAD;

        float cr = std::cos(roll * 0.5f);
        float sr = std::sin(roll * 0.5f);
        float cp = std::cos(pitch * 0.5f);
        float sp = std::sin(pitch * 0.5f);
        float cy = std::cos(yaw * 0.5f);
        float sy = std::sin(yaw * 0.5f);

        float w = cr * cp * cy + sr * sp * sy;
        float x = sr * cp * cy - cr * sp * sy;
        float y = cr * sp * cy + sr * cp * sy;
        float z = cr * cp * sy - sr * sp * cy;

        return AstrumQuaternion{ w, x, y, z };
    }

    // --- 연산자 오버로딩 (Operator Overloading) ---

    // 쿼터니언 곱셈 (SSE 최적화가 복잡하므로 C++ 유지)
    inline AstrumQuaternion operator*(const AstrumQuaternion& rhs) const {
        // 사원수 곱셈 공식
        float nw = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
        float nx = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
        float ny = W * rhs.Y - X * rhs.Z + Y * rhs.W + Z * rhs.X;
        float nz = W * rhs.Z + X * rhs.Y - Y * rhs.X + Z * rhs.W;
        return AstrumQuaternion{ nw, nx, ny, nz };
    }

    // 스칼라 곱셈 (SSE 최적화)
    constexpr AstrumQuaternion operator*(float scalar) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumQuaternion(_mm_mul_ps(m128, _mm_set1_ps(scalar)));
        }
#endif
        return { W * scalar, X * scalar, Y * scalar, Z * scalar };
    }

    // 스칼라 복합 대입 (SSE 최적화)
    constexpr AstrumQuaternion& operator*=(float scalar) {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            m128 = _mm_mul_ps(m128, _mm_set1_ps(scalar));
            return *this;
        }
#endif
        W *= scalar; X *= scalar; Y *= scalar; Z *= scalar;
        return *this;
    }

    // --- 멤버 함수 (Member Functions) ---

    // 벡터 회전 (Vector3 기반 연산이므로 C++ 유지)
    inline AstrumVector3 Rotate(const AstrumVector3& v) const {
        // 이미 최적화된 공식을 사용하고 계십니다 (q * v * q_inv 보다 빠름)
        AstrumVector3 qVec{ X, Y, Z };
        AstrumVector3 t = qVec.Cross(v);
        t.X *= 2.0f; t.Y *= 2.0f; t.Z *= 2.0f;

        AstrumVector3 vt = t;
        vt.X *= W; vt.Y *= W; vt.Z *= W;
        AstrumVector3 crossQT = qVec.Cross(t);

        return AstrumVector3{
            v.X + vt.X + crossQT.X,
            v.Y + vt.Y + crossQT.Y,
            v.Z + vt.Z + crossQT.Z
        };
    }

    // 정규화 (SSE 최적화)
    inline AstrumQuaternion Normalized() const {
        // Vector4의 Magnitude와 유사하게 길이의 제곱을 먼저 구합니다.
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            __m128 v = m128;
            __m128 dp = _mm_mul_ps(v, v);      // (W*W, X*X, Y*Y, Z*Z)
            dp = _mm_hadd_ps(dp, dp);       // (W*W+X*X, Y*Y+Z*Z, ...)
            dp = _mm_hadd_ps(dp, dp);       // (W*W+X*X+Y*Y+Z*Z, ...)

            // 0으로 나누는 것을 방지 (엡실론 값 사용)
            if (_mm_cvtss_f32(dp) < 1e-8f) {
                return Identity();
            }

            __m128 rsqrt = _mm_rsqrt_ss(dp); // 1 / sqrt(len) (빠른 근사치)
            // (참고: 더 정확한 값을 원하면 뉴턴-랩슨 반복을 한 번 더 할 수 있습니다)
            __m128 len_inv = _mm_shuffle_ps(rsqrt, rsqrt, _MM_SHUFFLE(0, 0, 0, 0)); // 모든 요소에 1/len

            return AstrumQuaternion(_mm_mul_ps(v, len_inv));
        }
#endif
        float lenSq = W * W + X * X + Y * Y + Z * Z;
        if (lenSq < 1e-8f) return Identity();
        float len = std::sqrt(lenSq);
        return { W / len, X / len, Y / len, Z / len };
    }

    // 켤레 (SSE 최적화)
    constexpr AstrumQuaternion Conjugate() const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            // (1.0, -1.0, -1.0, -1.0)과 곱하기
            return AstrumQuaternion(_mm_mul_ps(m128, _mm_set_ps(-1.f, -1.f, -1.f, 1.f)));
        }
#endif
        return AstrumQuaternion{ W, -X, -Y, -Z };
    }

    // 역 (SSE 최적화)
    inline AstrumQuaternion Inverse() const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            __m128 v = m128;
            __m128 dp = _mm_mul_ps(v, v);
            dp = _mm_hadd_ps(dp, dp);
            dp = _mm_hadd_ps(dp, dp); // 길이의 제곱 (lenSq)

            if (_mm_cvtss_f32(dp) < 1e-8f) {
                return Identity();
            }

            // 1.0f / lenSq
            __m128 invLenSq = _mm_div_ss(_mm_set_ss(1.0f), dp);
            invLenSq = _mm_shuffle_ps(invLenSq, invLenSq, _MM_SHUFFLE(0, 0, 0, 0));

            // Conjugate
            __m128 conj = _mm_mul_ps(v, _mm_set_ps(-1.f, -1.f, -1.f, 1.f));

            // Conjugate * (1.0f / lenSq)
            return AstrumQuaternion(_mm_mul_ps(conj, invLenSq));
        }
#endif
        float lenSq = W * W + X * X + Y * Y + Z * Z;
        if (lenSq < 1e-8f) return Identity();
        return Conjugate() * (1.0f / lenSq);
    }

    // 오일러 각 변환 (삼각함수 기반이므로 C++ 유지)
    inline AstrumVector3 ToEuler() const {
        AstrumVector3 euler;
        // X축 회전
        euler.X = std::atan2(
            2.0f * (W * X + Y * Z),
            1.0f - 2.0f * (X * X + Y * Y)
        );

        // Y축 회전
        float sinp = 2.0f * (W * Y - Z * X);
        if (std::fabs(sinp) >= 1.0f)
            euler.Y = std::copysign(std::numbers::pi_v<float> / 2.0f, sinp); // 90° 클램핑
        else
            euler.Y = std::asin(sinp);

        // Z축 회전
        euler.Z = std::atan2(
            2.0f * (W * Z + X * Y),
            1.0f - 2.0f * (Y * Y + Z * Z)
        );

        // 라디안 → 도 단위
        euler.X *= RAD2DEG;
        euler.Y *= RAD2DEG;
        euler.Z *= RAD2DEG;

        return euler;
    }
};

// .cpp 파일에 있던 내용들을 헤더 파일로 모두 이동
#undef ASTRUM_USE_SSE