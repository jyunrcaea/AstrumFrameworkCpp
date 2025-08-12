#include "AstrumObservedVector3.hpp"

AstrumObservedVector3::AstrumObservedVector3(AstrumObservedVector3&& vec3) noexcept
    : onChange(vec3.onChange), value(vec3.value) { }

AstrumObservedVector3::AstrumObservedVector3(const Callback& onChange) noexcept
    : onChange(onChange) {
}

AstrumObservedVector3::AstrumObservedVector3(float x, float y, float z, const Callback& onChange) noexcept
    : value(x, y, z), onChange(onChange) { }

AstrumObservedVector3::AstrumObservedVector3(const AstrumVector3& v, const Callback& onChange) noexcept
    : value(v), onChange(onChange) { }

AstrumObservedVector3::operator AstrumVector3() const noexcept { return value; }

float AstrumObservedVector3::GetX() const noexcept { return value.X; }
float AstrumObservedVector3::GetY() const noexcept { return value.Y; }
float AstrumObservedVector3::GetZ() const noexcept { return value.Z; }

void AstrumObservedVector3::SetX(float x) { value.X = x; Notify(); }
void AstrumObservedVector3::SetY(float y) { value.Y = y; Notify(); }
void AstrumObservedVector3::SetZ(float z) { value.Z = z; Notify(); }

void AstrumObservedVector3::AddX(float x) { value.X += x; Notify(); }
void AstrumObservedVector3::AddY(float y) { value.Y += y; Notify(); }
void AstrumObservedVector3::AddZ(float z) { value.Z += z; Notify(); }

void AstrumObservedVector3::Reset(const AstrumVector3& v) {
    value = v; Notify();
}
void AstrumObservedVector3::Reset(const AstrumObservedVector3& v) {
    value = v.value; Notify();
}

void AstrumObservedVector3::Reset(float x, float y, float z) {
    if (false == std::isnan(x)) value.X = x;
    if (false == std::isnan(y)) value.Y = y;
    if (false == std::isnan(z)) value.Z = z;
     Notify();
}

AstrumVector3 AstrumObservedVector3::operator+(const AstrumObservedVector3& o) const noexcept {
    return { value.X + o.value.X, value.Y + o.value.Y, value.Z + o.value.Z };
}

AstrumVector3 AstrumObservedVector3::operator-(const AstrumObservedVector3& o) const noexcept {
    return { value.X - o.value.X, value.Y - o.value.Y, value.Z - o.value.Z };
}

AstrumVector3 AstrumObservedVector3::operator*(float scalar) const noexcept {
    return { value.X * scalar, value.Y * scalar, value.Z * scalar };
}

AstrumVector3 AstrumObservedVector3::operator/(float scalar) const noexcept {
    return { value.X / scalar, value.Y / scalar, value.Z / scalar };
}

AstrumVector3 AstrumObservedVector3::operator*(const AstrumObservedVector3& o) const noexcept {
    return { value.X * o.GetX(), value.Y * o.GetY(), value.Z * o.GetZ() };
}

AstrumVector3 AstrumObservedVector3::operator/(const AstrumObservedVector3& o) const noexcept {
    return { value.X / o.GetX(), value.Y / o.GetY(), value.Z / o.GetZ() };
}

AstrumVector3 AstrumObservedVector3::operator+(const AstrumVector3& v) const noexcept {
    return { value.X + v.X, value.Y + v.Y, value.Z + v.Z };
}

AstrumVector3 AstrumObservedVector3::operator-(const AstrumVector3& v) const noexcept {
    return { value.X - v.X, value.Y - v.Y, value.Z - v.Z };
}

AstrumObservedVector3& AstrumObservedVector3::operator+=(const AstrumObservedVector3& o) {
    value += o.value; Notify();
    return *this;
}

AstrumObservedVector3& AstrumObservedVector3::operator-=(const AstrumObservedVector3& o) {
    value -= o.value; Notify();
    return *this;
}

AstrumObservedVector3& AstrumObservedVector3::operator*=(float scalar) {
    value *= scalar; Notify();
    return *this;
}

AstrumObservedVector3& AstrumObservedVector3::operator/=(float scalar) {
    value /= scalar; Notify();
    return *this;
}

AstrumVector3 AstrumObservedVector3::operator*(const AstrumVector3& v) const noexcept {
    return AstrumVector3{ value.X * v.X, value.Y * v.Y, value.Z * v.Z };
}

AstrumVector3 AstrumObservedVector3::operator/(const AstrumVector3& v) const noexcept {
    return AstrumVector3{ value.X / v.X, value.Y * v.Y, value.Z * v.Z };
}

void AstrumObservedVector3::Notify() {
    if (onChange) onChange();
}