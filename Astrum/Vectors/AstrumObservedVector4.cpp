#include "AstrumObservedVector4.hpp"

namespace Astrum
{
	ObservedVector4::ObservedVector4() = default;
	ObservedVector4::ObservedVector4(const Callback& onChange)
		: onChange_(onChange) {
	}
	ObservedVector4::ObservedVector4(float x, float y, float z, float w, const Callback& onChange)
		: value_(x, y, z, w), onChange_(onChange) {
	}
	ObservedVector4::ObservedVector4(const Vector4& v, const Callback& onChange)
		: value_(v), onChange_(onChange) {
	}

	ObservedVector4::operator Vector4() const {
		return value_;
	}

	float ObservedVector4::GetX() const { return value_.X; }
	float ObservedVector4::GetY() const { return value_.Y; }
	float ObservedVector4::GetZ() const { return value_.Z; }
	float ObservedVector4::GetW() const { return value_.W; }

	void ObservedVector4::SetX(float x) { value_.X = x; Notify(); }
	void ObservedVector4::SetY(float y) { value_.Y = y; Notify(); }
	void ObservedVector4::SetZ(float z) { value_.Z = z; Notify(); }
	void ObservedVector4::SetW(float w) { value_.W = w; Notify(); }

	// Reset
	void ObservedVector4::Reset(const Vector4& v) {
		value_ = v; Notify();
	}
	void ObservedVector4::Reset(float x, float y, float z, float w) {
		value_.X = x;
		value_.Y = y;
		value_.Z = z;
		value_.W = w;
		Notify();
	}

	Vector4 ObservedVector4::operator+(const ObservedVector4& o) const {
		return { value_.X + o.value_.X, value_.Y + o.value_.Y, value_.Z + o.value_.Z, value_.W + o.value_.W };
	}
	Vector4 ObservedVector4::operator-(const ObservedVector4& o) const {
		return { value_.X - o.value_.X, value_.Y - o.value_.Y, value_.Z - o.value_.Z, value_.W - o.value_.W };
	}
	Vector4 ObservedVector4::operator*(float scalar) const {
		return { value_.X * scalar, value_.Y * scalar, value_.Z * scalar, value_.W * scalar };
	}
	Vector4 ObservedVector4::operator/(float scalar) const {
		return { value_.X / scalar, value_.Y / scalar, value_.Z / scalar, value_.W / scalar };
	}

	ObservedVector4& ObservedVector4::operator+=(const ObservedVector4& o) {
		value_ += o.value_; Notify(); return *this;
	}
	ObservedVector4& ObservedVector4::operator-=(const ObservedVector4& o) {
		value_ -= o.value_; Notify(); return *this;
	}
	ObservedVector4& ObservedVector4::operator*=(float scalar) {
		value_ *= scalar; Notify(); return *this;
	}
	ObservedVector4& ObservedVector4::operator/=(float scalar) {
		value_ /= scalar; Notify(); return *this;
	}

	Vector4 ObservedVector4::operator+(const Vector4& v) const {
		return { value_.X + v.X, value_.Y + v.Y, value_.Z + v.Z, value_.W + v.W };
	}
	Vector4 ObservedVector4::operator-(const Vector4& v) const {
		return { value_.X - v.X, value_.Y - v.Y, value_.Z - v.Z, value_.W - v.W };
	}

	// Notify callback
	void ObservedVector4::Notify() {
		if (onChange_) onChange_();
	}
}
