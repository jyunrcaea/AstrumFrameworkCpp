#include "AstrumObservedVector2.hpp"

constexpr AstrumObservedVector2::AstrumObservedVector2() = default;

AstrumObservedVector2::AstrumObservedVector2(const Callback& onChange)
    : onChange_(onChange) {
}

AstrumObservedVector2::AstrumObservedVector2(float x, float y, const Callback& onChange)
    : value_(x, y), onChange_(onChange) {
}

AstrumObservedVector2::AstrumObservedVector2(const AstrumVector2& v, const Callback& onChange)
    : value_(v), onChange_(onChange) {
}

AstrumObservedVector2::operator AstrumVector2() const {
    return value_;
}

float AstrumObservedVector2::GetX() const {
    return value_.X; 
}

float AstrumObservedVector2::GetY() const {
    return value_.Y;
}

void AstrumObservedVector2::SetX(float x) {
    value_.X = x;
    Notify();
}

void AstrumObservedVector2::SetY(float y) {
    value_.Y = y;
    Notify();
}

void AstrumObservedVector2::Reset(const AstrumVector2& v) {
    value_ = v;
    Notify();
}

void AstrumObservedVector2::Reset(float x, float y) {
    value_.X = x;
    value_.Y = y;
    Notify();
}

AstrumVector2 AstrumObservedVector2::operator+(const AstrumObservedVector2& o) const {
    return { value_.X + o.value_.X, value_.Y + o.value_.Y };
}

AstrumVector2 AstrumObservedVector2::operator-(const AstrumObservedVector2& o) const {
    return { value_.X - o.value_.X, value_.Y - o.value_.Y };
}

AstrumVector2 AstrumObservedVector2::operator*(float scalar) const {
    return { value_.X * scalar, value_.Y * scalar };
}

AstrumVector2 AstrumObservedVector2::operator/(float scalar) const {
    return { value_.X / scalar, value_.Y / scalar };
}

AstrumVector2 AstrumObservedVector2::operator+(const AstrumVector2& v) const {
    return { value_.X + v.X, value_.Y + v.Y };
}

AstrumVector2 AstrumObservedVector2::operator-(const AstrumVector2& v) const {
    return { value_.X - v.X, value_.Y - v.Y };
}

void AstrumObservedVector2::Notify() {
    if (onChange_) {
        onChange_();
    }
}

AstrumObservedVector2& AstrumObservedVector2::operator+=(const AstrumObservedVector2& other) {
    value_.X += other.GetX();
    value_.Y += other.GetY();
    Notify();
    return *this;
}

AstrumObservedVector2& AstrumObservedVector2::operator-=(const AstrumObservedVector2& other) {
    value_.X -= other.GetX();
    value_.Y -= other.GetY();
    Notify();
    return *this;
}

AstrumObservedVector2& AstrumObservedVector2::operator*=(float scalar) {
    value_.X *= scalar;
    value_.Y *= scalar;
    Notify();
    return *this;
}

AstrumObservedVector2& AstrumObservedVector2::operator/=(float scalar) {
    value_.X /= scalar;
    value_.Y /= scalar;
    Notify();
    return *this;
}