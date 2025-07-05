#pragma once
#include <cmath>

struct AstrumVector3 {
    float X{ 0.0f }, Y{ 0.0f }, Z{ 0.0f };

    constexpr AstrumVector3() = default;
    constexpr AstrumVector3(float x, float y, float z = 0)
        : X(x), Y(y), Z(z) {
    }

    // 멤버 함수 선언
    float Magnitude() const;
    AstrumVector3 Normalize() const;
    float Distance(const AstrumVector3& other) const;
    float Dot(const AstrumVector3& other) const;
    AstrumVector3 Cross(const AstrumVector3& other) const;

    // 정적 상수 원점
    static const AstrumVector3 Origin;

    // 연산자
    AstrumVector3 operator+(const AstrumVector3& v) const;
    AstrumVector3 operator-(const AstrumVector3& v) const;
    AstrumVector3 operator*(float scalar) const;
    AstrumVector3 operator/(float scalar) const;
};