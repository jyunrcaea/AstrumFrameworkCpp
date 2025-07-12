#pragma once

#include "AstrumVector3.hpp"
#include <functional>

class AstrumObservedVector3 {
public:
    using Callback = std::function<void()>;

    AstrumObservedVector3();
    explicit AstrumObservedVector3(const Callback& onChange);
    AstrumObservedVector3(float x, float y, float z, const Callback& onChange = {});
    AstrumObservedVector3(const AstrumVector3& v, const Callback& onChange = {});

    operator AstrumVector3() const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

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