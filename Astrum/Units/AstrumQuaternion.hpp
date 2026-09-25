#pragma once
#include <numbers>
#include <cmath>
#include <algorithm> // for std::is_constant_evaluated
#include <cstddef>
#include "../Vectors/AstrumVector3.hpp"

// Vector4와 마찬가지로 SSE 지원 여부를 확인합니다.
// SSE2 사용 여부. (GCC/Clang은 __SSE2__, MSVC는 x64 또는 /arch:SSE2 이상일 때 _M_X64/_M_IX86_FP로 확인)
// 다른 헤더가 같은 이름의 매크로를 쓰더라도 영향을 주지 않도록 push/pop 합니다.
#pragma push_macro("ASTRUM_USE_SSE")
#undef ASTRUM_USE_SSE
#if defined(__SSE2__) || defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
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
#if ASTRUM_USE_SSE
    // 메모리 배치는 SSE 사용 여부와 관계없이 float 4개(W, X, Y, Z)로 동일하게 유지하고, 연산할 때만 SSE 레지스터로 읽고 씁니다.
    /// <summary>
    /// SSE 128비트 레지스터로부터 사원수를 생성합니다. (W, X, Y, Z 순서)
    /// </summary>
    AstrumQuaternion(__m128 vec) { Store(vec); }
    /// <summary>
    /// 사원수를 SSE 128비트 레지스터로 읽어옵니다. (W, X, Y, Z 순서)
    /// </summary>
    __m128 Load() const { return _mm_loadu_ps(&W); }
    /// <summary>
    /// SSE 128비트 레지스터의 값을 사원수에 씁니다.
    /// </summary>
    void Store(__m128 vec) { _mm_storeu_ps(&W, vec); }
private:
    // 네 성분의 합을 모든 요소에 채워 반환합니다. (SSE2 명령어만 사용)
    static __m128 HorizontalSum(__m128 v) {
        __m128 shuffled = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1)); // (b, a, d, c)
        __m128 sums = _mm_add_ps(v, shuffled);                          // (a+b, a+b, c+d, c+d)
        shuffled = _mm_shuffle_ps(sums, sums, _MM_SHUFFLE(1, 0, 3, 2));  // (c+d, c+d, a+b, a+b)
        return _mm_add_ps(sums, shuffled);                              // (a+b+c+d, ...)
    }
public:
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
            return AstrumQuaternion(_mm_mul_ps(Load(), _mm_set1_ps(scalar)));
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
            Store(_mm_mul_ps(Load(), _mm_set1_ps(scalar)));
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
            __m128 v = Load();
            __m128 dp = HorizontalSum(_mm_mul_ps(v, v)); // (W*W+X*X+Y*Y+Z*Z, ...)

            // 0으로 나누는 것을 방지 (엡실론 값 사용)
            if (_mm_cvtss_f32(dp) < 1e-8f) {
                return Identity();
            }

            // 정확한 제곱근으로 나눕니다. (역제곱근 근사 명령은 오차가 커서 회전이 조금씩 틀어질 수 있음)
            return AstrumQuaternion(_mm_div_ps(v, _mm_sqrt_ps(dp)));
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
            return AstrumQuaternion(_mm_mul_ps(Load(), _mm_set_ps(-1.f, -1.f, -1.f, 1.f)));
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
            __m128 v = Load();
            __m128 dp = HorizontalSum(_mm_mul_ps(v, v)); // 길이의 제곱 (lenSq)

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
// SSE 연산은 W부터 연속된 float 4개를 읽고 쓰므로, 패딩 없이 16바이트로 배치되어야 합니다.
static_assert(sizeof(AstrumQuaternion) == sizeof(float) * 4 && offsetof(AstrumQuaternion, Z) == sizeof(float) * 3);

#pragma pop_macro("ASTRUM_USE_SSE")
