#pragma once
#include "AstrumVector2.hpp"
#include <functional>

class AstrumObservedVector2 {
public:
    using Callback = std::function<void()>;

    constexpr AstrumObservedVector2();
    explicit AstrumObservedVector2(const Callback& onChange);
    AstrumObservedVector2(float x, float y, const Callback& onChange = {});
    AstrumObservedVector2(const AstrumVector2& v, const Callback& onChange = {});

    operator AstrumVector2() const;

    float GetX() const;
    float GetY() const;

    void SetX(float x);
    void SetY(float y);

    void Reset(const AstrumVector2& v);
    void Reset(float x, float y);

    AstrumVector2 operator+(const AstrumObservedVector2& o) const;
    AstrumVector2 operator-(const AstrumObservedVector2& o) const;
    AstrumVector2 operator*(float scalar) const;
    AstrumVector2 operator/(float scalar) const;

    AstrumObservedVector2& operator+=(const AstrumObservedVector2& other);
    AstrumObservedVector2& operator-=(const AstrumObservedVector2& other);
    AstrumObservedVector2& operator*=(float scalar);
    AstrumObservedVector2& operator/=(float scalar);

    AstrumVector2 operator+(const AstrumVector2& v) const;
    AstrumVector2 operator-(const AstrumVector2& v) const;

private:
    AstrumVector2 value_{ 0.0f, 0.0f };
    Callback onChange_;

    void Notify();
};