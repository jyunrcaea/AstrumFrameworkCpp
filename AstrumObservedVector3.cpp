#include "AstrumObservedVector3.hpp"

AstrumObservedVector3::AstrumObservedVector3(AstrumObservedVector3&& vec3) noexcept
    : onChange_(vec3.onChange_), value_(vec3.value_) { }

AstrumObservedVector3::AstrumObservedVector3(const Callback& onChange) noexcept
    : onChange_(onChange) {
}

AstrumObservedVector3::AstrumObservedVector3(float x, float y, float z, const Callback& onChange) noexcept
    : value_(x, y, z), onChange_(onChange) {
}

AstrumObservedVector3::AstrumObservedVector3(const AstrumVector3& v, const Callback& onChange) noexcept
    : value_(v), onChange_(onChange) {
}

AstrumObservedVector3::operator AstrumVector3() const {
    return value_;
}

float AstrumObservedVector3::GetX() const noexcept { return value_.X; }
float AstrumObservedVector3::GetY() const noexcept { return value_.Y; }
float AstrumObservedVector3::GetZ() const noexcept { return value_.Z; }

void AstrumObservedVector3::SetX(float x) { value_.X = x; Notify(); } // 값이 바뀔때마다 notify()를 호출하고
void AstrumObservedVector3::SetY(float y) { value_.Y = y; Notify(); }
void AstrumObservedVector3::SetZ(float z) { value_.Z = z; Notify(); }

void AstrumObservedVector3::AddX(float x) { value_.X += x; Notify(); }
void AstrumObservedVector3::AddY(float y) { value_.Y += y; Notify(); }
void AstrumObservedVector3::AddZ(float z) { value_.Z += z; Notify(); }

void AstrumObservedVector3::Reset(const AstrumVector3& v) {
    value_ = v; Notify();
}
void AstrumObservedVector3::Reset(const AstrumObservedVector3& v) {
    value_ = v.value_; Notify();
}

void AstrumObservedVector3::Reset(float x, float y, float z) {
    value_.X = x; value_.Y = y; value_.Z = z; Notify();
}

AstrumVector3 AstrumObservedVector3::operator+(const AstrumObservedVector3& o) const noexcept {
    return { value_.X + o.value_.X, value_.Y + o.value_.Y, value_.Z + o.value_.Z };
}

AstrumVector3 AstrumObservedVector3::operator-(const AstrumObservedVector3& o) const noexcept {
    return { value_.X - o.value_.X, value_.Y - o.value_.Y, value_.Z - o.value_.Z };
}

AstrumVector3 AstrumObservedVector3::operator*(float scalar) const noexcept {
    return { value_.X * scalar, value_.Y * scalar, value_.Z * scalar };
}

AstrumVector3 AstrumObservedVector3::operator/(float scalar) const noexcept {
    return { value_.X / scalar, value_.Y / scalar, value_.Z / scalar };
}

AstrumVector3 AstrumObservedVector3::operator*(const AstrumObservedVector3& o) const noexcept {
    return { value_.X * o.GetX(), value_.Y * o.GetY(), value_.Z * o.GetZ() };
}

AstrumVector3 AstrumObservedVector3::operator/(const AstrumObservedVector3& o) const noexcept {
    return { value_.X / o.GetX(), value_.Y / o.GetY(), value_.Z / o.GetZ() };
}

AstrumVector3 AstrumObservedVector3::operator+(const AstrumVector3& v) const noexcept {
    return { value_.X + v.X, value_.Y + v.Y, value_.Z + v.Z };
}

AstrumVector3 AstrumObservedVector3::operator-(const AstrumVector3& v) const noexcept {
    return { value_.X - v.X, value_.Y - v.Y, value_.Z - v.Z };
}

AstrumObservedVector3& AstrumObservedVector3::operator+=(const AstrumObservedVector3& o) {
    value_ += o.value_; Notify();
    return *this;
}

AstrumObservedVector3& AstrumObservedVector3::operator-=(const AstrumObservedVector3& o) {
    value_ -= o.value_; Notify();
    return *this;
}

AstrumObservedVector3& AstrumObservedVector3::operator*=(float scalar) {
    value_ *= scalar; Notify();
    return *this;
}

AstrumObservedVector3& AstrumObservedVector3::operator/=(float scalar) {
    value_ /= scalar; Notify();
    return *this;
}

AstrumVector3 AstrumObservedVector3::operator*(const AstrumVector3& v) const noexcept {
    return AstrumVector3{ value_.X * v.X, value_.Y * v.Y, value_.Z * v.Z };
}

AstrumVector3 AstrumObservedVector3::operator/(const AstrumVector3& v) const noexcept {
    return AstrumVector3{ value_.X / v.X, value_.Y * v.Y, value_.Z * v.Z };
}

void AstrumObservedVector3::Notify() {
    if (onChange_) onChange_();
}