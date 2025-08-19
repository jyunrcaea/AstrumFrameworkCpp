#pragma once

#include "AstrumVector3.hpp"
#include <functional>

// x,y,z가 바뀌는걸 감지하는 vector3
class AstrumObservedVector3 {
public:
    using Callback = std::function<void()>;

    AstrumObservedVector3(AstrumObservedVector3&& vec3) noexcept;
    // 값이 바뀔때마다 호출되는 함수를 정의할수 있습니다.
    explicit AstrumObservedVector3(const Callback& onChange) noexcept;
    AstrumObservedVector3(float x, float y, float z, const Callback& onChange = {}) noexcept;
    // 이걸 만든 이유는, 크기/회전/좌표가 바뀔때마다
    // 게임 객체가 트리 구조로 되어 있잖아요?
    // 부모가 바뀌면, 자식도 같이 영향을 받아요, 그래서 만약 부모가 스케일을 2로 키우면, 자식은 크기도 2배가 되고, x를 한칸 이동하면 실제로 2칸을 이동해요.
    AstrumObservedVector3(const AstrumVector3& v, const Callback& onChange = {}) noexcept;

    operator AstrumVector3() const noexcept;

    float GetX() const noexcept;
    float GetY() const noexcept;
    float GetZ() const noexcept;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    void AddX(float x);
    void AddY(float y);
    void AddZ(float z);

    void Reset(const AstrumVector3& v);
    void Reset(const AstrumObservedVector3& v);
    // NAN일 경우 기존 값이 할당됩니다.
    void Reset(float x, float y, float z = NAN);

    AstrumVector3 operator+(const AstrumObservedVector3& o) const noexcept;
    AstrumVector3 operator-(const AstrumObservedVector3& o) const noexcept;
    AstrumVector3 operator*(float scalar) const noexcept;
    AstrumVector3 operator/(float scalar) const noexcept;

    AstrumVector3 operator*(const AstrumObservedVector3& o) const noexcept;
    AstrumVector3 operator/(const AstrumObservedVector3& o) const noexcept;

    AstrumVector3 operator+(const AstrumVector3& v) const noexcept;
    AstrumVector3 operator-(const AstrumVector3& v) const noexcept;
    AstrumVector3 operator*(const AstrumVector3& v) const noexcept;
    AstrumVector3 operator/(const AstrumVector3& v) const noexcept;

    AstrumObservedVector3& operator+=(const AstrumObservedVector3& o);
    AstrumObservedVector3& operator-=(const AstrumObservedVector3& o);
    AstrumObservedVector3& operator*=(float scalar);
    AstrumObservedVector3& operator/=(float scalar);

private:
    AstrumVector3 value{ 0.0f, 0.0f, 0.0f };
    Callback onChange;

    void Notify();
};