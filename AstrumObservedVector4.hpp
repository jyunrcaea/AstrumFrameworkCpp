#pragma once

#include "AstrumVector4.hpp"
#include <functional>

class AstrumObservedVector4 {
public:
    using Callback = std::function<void()>;

    AstrumObservedVector4();
    explicit AstrumObservedVector4(const Callback& onChange);
    AstrumObservedVector4(float x, float y, float z, float w, const Callback& onChange = {});
    AstrumObservedVector4(const AstrumVector4& v, const Callback& onChange = {});

    operator AstrumVector4() const;

    // Accessors
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetW() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
    void SetW(float w);

    void Reset(const AstrumVector4& v);
    void Reset(float x, float y, float z, float w);

    AstrumVector4 operator+(const AstrumObservedVector4& o) const;
    AstrumVector4 operator-(const AstrumObservedVector4& o) const;
    AstrumVector4 operator*(float scalar) const;
    AstrumVector4 operator/(float scalar) const;

    AstrumObservedVector4& operator+=(const AstrumObservedVector4& o);
    AstrumObservedVector4& operator-=(const AstrumObservedVector4& o);
    AstrumObservedVector4& operator*=(float scalar);
    AstrumObservedVector4& operator/=(float scalar);

    AstrumVector4 operator+(const AstrumVector4& v) const;
    AstrumVector4 operator-(const AstrumVector4& v) const;

private:
    AstrumVector4 value_{ 0.0f, 0.0f, 0.0f, 0.0f };
    Callback onChange_;

    void Notify();
};