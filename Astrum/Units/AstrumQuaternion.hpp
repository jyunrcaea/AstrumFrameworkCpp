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
    /// <summary>
    /// 도(degree)를 라디안(radian)으로 변환하는 상수입니다.
    /// </summary>
    constexpr float DEG2RAD = static_cast<float>(std::numbers::pi / 180.0);
    /// <summary>
    /// 라디안(radian)을 도(degree)로 변환하는 상수입니다.
    /// </summary>
    constexpr float RAD2DEG = static_cast<float>(180.0 / std::numbers::pi);
}

/// <summary>
/// 사원수(쿼터니언)를 나타내는 구조체입니다.
/// 3D 회전을 효율적으로 표현하고 조합할 수 있습니다.
/// SSE 명령어를 지원하는 경우 SIMD 최적화를 사용합니다.
/// </summary>
struct AstrumQuaternion {
#if ASTRUM_USE_SSE
    /// <summary>
    /// SSE 지원 시 공용체로 정의됩니다. 개별 성분 또는 128비트 SIMD 레지스터로 접근 가능합니다.
    /// </summary>
    union {
        struct { 
            /// <summary>
            /// 스칼라 성분(회전 축)입니다.
            /// </summary>
            float W, 
            /// <summary>
            /// 벡터 성분 X입니다.
            /// </summary>
            X, 
            /// <summary>
            /// 벡터 성분 Y입니다.
            /// </summary>
            Y, 
            /// <summary>
            /// 벡터 성분 Z입니다.
            /// </summary>
            Z; 
        };
        __m128 m128;
    };
    /// <summary>
    /// SSE 128비트 레지스터로부터 사원수를 생성합니다.
    /// </summary>
    /// <param name="vec">SSE 레지스터입니다.</param>
    AstrumQuaternion(__m128 vec) : m128(vec) {}
#else
    /// <summary>
    /// 스칼라 성분(회전 축)입니다.
    /// </summary>
    float W, 
    /// <summary>
    /// 벡터 성분 X입니다.
    /// </summary>
    X, 
    /// <summary>
    /// 벡터 성분 Y입니다.
    /// </summary>
    Y, 
    /// <summary>
    /// 벡터 성분 Z입니다.
    /// </summary>
    Z;
#endif

    /// <summary>
    /// 기본 생성자입니다. (0, 0, 0, 0)으로 초기화됩니다.
    /// </summary>
    constexpr AstrumQuaternion() : W(0.0f), X(0.0f), Y(0.0f), Z(0.0f) {}
    /// <summary>
    /// 지정된 W, X, Y, Z 값으로 사원수를 생성합니다.
    /// </summary>
    /// <param name="w">스칼라 성분입니다.</param>
    /// <param name="x">벡터 성분 X입니다.</param>
    /// <param name="y">벡터 성분 Y입니다.</param>
    /// <param name="z">벡터 성분 Z입니다.</param>
    constexpr AstrumQuaternion(float w, float x, float y, float z) : W(w), X(x), Y(y), Z(z) {}

    /// <summary>
    /// 항등 사원수를 반환합니다. (회전이 없음)
    /// </summary>
    /// <returns>항등 사원수 (1, 0, 0, 0)입니다.</returns>
    static inline AstrumQuaternion Identity() {
        return AstrumQuaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
    }

    /// <summary>
    /// 축과 각도로부터 사원수를 생성합니다.
    /// </summary>
    /// <param name="axis">회전 축입니다. (자동으로 정규화됨)</param>
    /// <param name="rad">회전 각도(라디안)입니다.</param>
    /// <returns>생성된 사원수입니다.</returns>
    static inline AstrumQuaternion FromAxisAngle(AstrumVector3 axis, float rad) {
        AstrumVector3 norm = axis.Normalize();
        float halfAngle = rad * 0.5f;
        float sinHalf = std::sin(halfAngle);
        float cosHalf = std::cos(halfAngle);
        return AstrumQuaternion{ cosHalf, norm.X * sinHalf, norm.Y * sinHalf, norm.Z * sinHalf };
    }

    /// <summary>
    /// 오일러 각(도 단위)으로부터 사원수를 생성합니다.
    /// </summary>
    /// <param name="deg">각 축의 회전(도)을 포함하는 벡터입니다. (X=롤, Y=피치, Z=요우)</param>
    /// <returns>생성된 사원수입니다.</returns>
    static inline AstrumQuaternion FromEuler(AstrumVector3 deg) {
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

    /// <summary>
    /// 두 사원수를 곱합니다. (사원수 곱셈)
    /// </summary>
    /// <param name="rhs">곱할 사원수입니다.</param>
    /// <returns>곱셈 결과 사원수입니다.</returns>
    inline AstrumQuaternion operator*(const AstrumQuaternion& rhs) const {
        float nw = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
        float nx = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
        float ny = W * rhs.Y - X * rhs.Z + Y * rhs.W + Z * rhs.X;
        float nz = W * rhs.Z + X * rhs.Y - Y * rhs.X + Z * rhs.W;
        return AstrumQuaternion{ nw, nx, ny, nz };
    }

    /// <summary>
    /// 사원수에 스칼라값을 곱합니다.
    /// </summary>
    /// <param name="scalar">곱할 스칼라값입니다.</param>
    /// <returns>곱셈 결과 사원수입니다.</returns>
    constexpr AstrumQuaternion operator*(float scalar) const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            return AstrumQuaternion(_mm_mul_ps(m128, _mm_set1_ps(scalar)));
        }
#endif
        return { W * scalar, X * scalar, Y * scalar, Z * scalar };
    }

    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// </summary>
    /// <param name="scalar">곱할 스칼라값입니다.</param>
    /// <returns>이 사원수의 참조입니다.</returns>
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

    /// <summary>
    /// 벡터를 이 사원수가 나타내는 회전만큼 회전시킵니다.
    /// </summary>
    /// <param name="v">회전할 벡터입니다.</param>
    /// <returns>회전된 벡터입니다.</returns>
    inline AstrumVector3 Rotate(const AstrumVector3& v) const {
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

    /// <summary>
    /// 정규화된 사원수를 반환합니다. (크기가 1인 사원수)
    /// </summary>
    /// <returns>정규화된 사원수입니다.</returns>
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

    /// <summary>
    /// 사원수의 켤레(conjugate)를 반환합니다.
    /// 켤레 사원수는 벡터 부분의 부호를 반전시킨 것입니다.
    /// </summary>
    /// <returns>켤레 사원수입니다.</returns>
    constexpr AstrumQuaternion Conjugate() const {
#if ASTRUM_USE_SSE
        if (false == std::is_constant_evaluated()) {
            // (1.0, -1.0, -1.0, -1.0)과 곱하기
            return AstrumQuaternion(_mm_mul_ps(m128, _mm_set_ps(-1.f, -1.f, -1.f, 1.f)));
        }
#endif
        return AstrumQuaternion{ W, -X, -Y, -Z };
    }

    /// <summary>
    /// 사원수의 역(inverse)을 반환합니다.
    /// 정규화된 사원수의 경우 켤레와 같습니다.
    /// </summary>
    /// <returns>역 사원수입니다.</returns>
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

    /// <summary>
    /// 사원수를 오일러 각(도 단위)으로 변환합니다.
    /// </summary>
    /// <returns>각 축의 회전(도)을 포함하는 벡터입니다. (X=롤, Y=피치, Z=요우)</returns>
    inline AstrumVector3 ToEuler() const {
        AstrumVector3 euler;
        // X축 회전 (롤)
        euler.X = std::atan2(
            2.0f * (W * X + Y * Z),
            1.0f - 2.0f * (X * X + Y * Y)
        );

        // Y축 회전 (피치)
        float sinp = 2.0f * (W * Y - Z * X);
        if (std::fabs(sinp) >= 1.0f)
            euler.Y = std::copysign(std::numbers::pi_v<float> / 2.0f, sinp); // 90° 클램핑
        else
            euler.Y = std::asin(sinp);

        // Z축 회전 (요우)
        euler.Z = std::atan2(
            2.0f * (W * Z + X * Y),
            1.0f - 2.0f * (Y * Y + Z * Z)
        );

        // 라디안 → 도 단위 변환
        euler.X *= RAD2DEG;
        euler.Y *= RAD2DEG;
        euler.Z *= RAD2DEG;

        return euler;
    }
};

// .cpp 파일에 있던 내용들을 헤더 파일로 모두 이동
#undef ASTRUM_USE_SSE