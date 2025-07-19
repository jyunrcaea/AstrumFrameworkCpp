#pragma once

#include "AstrumVector3.hpp"
#include <functional>

// 이게 조금 특이한데, 그냥 vector3가 아니라, x,y,z가 바뀌는걸 감지하는 vector3에요
class AstrumObservedVector3 {
public:
    using Callback = std::function<void()>;

    AstrumObservedVector3();
    // 콜백은 생성자에서 정의해요. 생성자에서 넣은 함수가, 값이 바뀔때마다 호출되는 함수에요.
    explicit AstrumObservedVector3(const Callback& onChange);
    AstrumObservedVector3(float x, float y, float z, const Callback& onChange = {});
    // 이걸 만든 이유는, 크기/회전/좌표가 바뀔때마다
    // 객체가 트리 구조로 되어 있잖아요?
    // 부모가 바뀌면, 자식도 같이 영향을 받아요, 그래서 만약 부모가 스케일을 2로 키우면, 자식은 크기도 2배가 되고, x를 한칸 이동하면 실제로 2칸을 이동해요.
    AstrumObservedVector3(const AstrumVector3& v, const Callback& onChange = {});

    operator AstrumVector3() const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    void AddX(float x);
    void AddY(float y);
    void AddZ(float z);

    void Reset(const AstrumVector3& v);
    void Reset(const AstrumObservedVector3& v);
    void Reset(float x, float y, float z);

    AstrumVector3 operator+(const AstrumObservedVector3& o) const;
    AstrumVector3 operator-(const AstrumObservedVector3& o) const;
    AstrumVector3 operator*(float scalar) const;
    AstrumVector3 operator/(float scalar) const;

    AstrumVector3 operator*(const AstrumObservedVector3& o) const;
    AstrumVector3 operator/(const AstrumObservedVector3& o) const;

    AstrumVector3 operator+(const AstrumVector3& v) const;
    AstrumVector3 operator-(const AstrumVector3& v) const;
    AstrumVector3 operator*(const AstrumVector3& v) const;
    AstrumVector3 operator/(const AstrumVector3& v) const;

    AstrumObservedVector3& operator+=(const AstrumObservedVector3& o);
    AstrumObservedVector3& operator-=(const AstrumObservedVector3& o);
    AstrumObservedVector3& operator*=(float scalar);
    AstrumObservedVector3& operator/=(float scalar);

private:
    AstrumVector3 value_{ 0.0f, 0.0f, 0.0f };
    Callback onChange_;

    void Notify();
};