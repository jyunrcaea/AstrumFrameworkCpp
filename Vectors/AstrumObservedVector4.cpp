#include "AstrumObservedVector4.hpp"

AstrumObservedVector4::AstrumObservedVector4() = default;
AstrumObservedVector4::AstrumObservedVector4(const Callback& onChange)
    : onChange_(onChange) {
}
AstrumObservedVector4::AstrumObservedVector4(float x, float y, float z, float w, const Callback& onChange)
    : value_(x, y, z, w), onChange_(onChange) {
}
AstrumObservedVector4::AstrumObservedVector4(const AstrumVector4& v, const Callback& onChange)
    : value_(v), onChange_(onChange) {
}

AstrumObservedVector4::operator AstrumVector4() const {
    return value_;
}

float AstrumObservedVector4::GetX() const { return value_.X; }
float AstrumObservedVector4::GetY() const { return value_.Y; }
float AstrumObservedVector4::GetZ() const { return value_.Z; }
float AstrumObservedVector4::GetW() const { return value_.W; }

void AstrumObservedVector4::SetX(float x) { value_.X = x; Notify(); }
void AstrumObservedVector4::SetY(float y) { value_.Y = y; Notify(); }
void AstrumObservedVector4::SetZ(float z) { value_.Z = z; Notify(); }
void AstrumObservedVector4::SetW(float w) { value_.W = w; Notify(); }

// Reset
void AstrumObservedVector4::Reset(const AstrumVector4& v) {
    value_ = v; Notify();
}
void AstrumObservedVector4::Reset(float x, float y, float z, float w) {
    value_.X = x;
    value_.Y = y;
    value_.Z = z;
    value_.W = w;
    Notify();
}

AstrumVector4 AstrumObservedVector4::operator+(const AstrumObservedVector4& o) const {
    return { value_.X + o.value_.X, value_.Y + o.value_.Y, value_.Z + o.value_.Z, value_.W + o.value_.W };
}
AstrumVector4 AstrumObservedVector4::operator-(const AstrumObservedVector4& o) const {
    return { value_.X - o.value_.X, value_.Y - o.value_.Y, value_.Z - o.value_.Z, value_.W - o.value_.W };
}
AstrumVector4 AstrumObservedVector4::operator*(float scalar) const {
    return { value_.X * scalar, value_.Y * scalar, value_.Z * scalar, value_.W * scalar };
}
AstrumVector4 AstrumObservedVector4::operator/(float scalar) const {
    return { value_.X / scalar, value_.Y / scalar, value_.Z / scalar, value_.W / scalar };
}

AstrumObservedVector4& AstrumObservedVector4::operator+=(const AstrumObservedVector4& o) {
    value_ += o.value_; Notify(); return *this;
}
AstrumObservedVector4& AstrumObservedVector4::operator-=(const AstrumObservedVector4& o) {
    value_ -= o.value_; Notify(); return *this;
}
AstrumObservedVector4& AstrumObservedVector4::operator*=(float scalar) {
    value_ *= scalar; Notify(); return *this;
}
AstrumObservedVector4& AstrumObservedVector4::operator/=(float scalar) {
    value_ /= scalar; Notify(); return *this;
}

AstrumVector4 AstrumObservedVector4::operator+(const AstrumVector4& v) const {
    return { value_.X + v.X, value_.Y + v.Y, value_.Z + v.Z, value_.W + v.W };
}
AstrumVector4 AstrumObservedVector4::operator-(const AstrumVector4& v) const {
    return { value_.X - v.X, value_.Y - v.Y, value_.Z - v.Z, value_.W - v.W };
}

// Notify callback
void AstrumObservedVector4::Notify() {
    if (onChange_) onChange_();
}
