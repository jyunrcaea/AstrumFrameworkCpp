#pragma once
#include <cmath>

struct AstrumVector4 {
    float X{ 0.0f }, Y{ 0.0f }, Z{ 0.0f }, W{ 0.0f };

    // constexpr 생성자는 헤더에 정의하여 컴파일 타임 상수로도 사용할 수 있게 합니다.
    constexpr AstrumVector4() = default;
    constexpr AstrumVector4(float x, float y, float z, float w = 0.0f)
        : X(x), Y(y), Z(z), W(w) {
    }

    // 멤버 함수 선언
    float Magnitude() const;
    AstrumVector4 Normalize() const;
    float Distance(const AstrumVector4& other) const;
    float Dot(const AstrumVector4& other) const;

    // 정적 상수 원점
    static const AstrumVector4 Origin;

    // 연산자
    AstrumVector4 operator+(const AstrumVector4& v) const;
    AstrumVector4 operator-(const AstrumVector4& v) const;
    AstrumVector4 operator*(float scalar) const;
    AstrumVector4 operator/(float scalar) const;
};