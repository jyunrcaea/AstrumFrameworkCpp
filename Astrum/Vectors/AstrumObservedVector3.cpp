#include "AstrumObservedVector3.hpp"

namespace Astrum
{
	ObservedVector3::ObservedVector3(ObservedVector3&& vec3) noexcept
		: onChange(vec3.onChange), value(vec3.value) { }

	ObservedVector3::ObservedVector3(const Callback& onChange) noexcept
		: onChange(onChange) {
	}

	ObservedVector3::ObservedVector3(float x, float y, float z, const Callback& onChange) noexcept
		: value(x, y, z), onChange(onChange) { }

	ObservedVector3::ObservedVector3(const Vector3& v, const Callback& onChange) noexcept
		: value(v), onChange(onChange) { }

	ObservedVector3::operator Vector3() const noexcept { return value; }

	float ObservedVector3::GetX() const noexcept { return value.X; }
	float ObservedVector3::GetY() const noexcept { return value.Y; }
	float ObservedVector3::GetZ() const noexcept { return value.Z; }

	void ObservedVector3::SetX(float x) { value.X = x; Notify(); }
	void ObservedVector3::SetY(float y) { value.Y = y; Notify(); }
	void ObservedVector3::SetZ(float z) { value.Z = z; Notify(); }

	void ObservedVector3::AddX(float x) { value.X += x; Notify(); }
	void ObservedVector3::AddY(float y) { value.Y += y; Notify(); }
	void ObservedVector3::AddZ(float z) { value.Z += z; Notify(); }

	void ObservedVector3::Reset(const Vector3& v) {
		value = v; Notify();
	}
	void ObservedVector3::Reset(const ObservedVector3& v) {
		value = v.value; Notify();
	}

	void ObservedVector3::Reset(float x, float y, float z) {
		if (false == std::isnan(x)) value.X = x;
		if (false == std::isnan(y)) value.Y = y;
		if (false == std::isnan(z)) value.Z = z;
		Notify();
	}

	Vector3 ObservedVector3::operator+(const ObservedVector3& o) const noexcept {
		return { value.X + o.value.X, value.Y + o.value.Y, value.Z + o.value.Z };
	}

	Vector3 ObservedVector3::operator-(const ObservedVector3& o) const noexcept {
		return { value.X - o.value.X, value.Y - o.value.Y, value.Z - o.value.Z };
	}

	Vector3 ObservedVector3::operator*(float scalar) const noexcept {
		return { value.X * scalar, value.Y * scalar, value.Z * scalar };
	}

	Vector3 ObservedVector3::operator/(float scalar) const noexcept {
		return { value.X / scalar, value.Y / scalar, value.Z / scalar };
	}

	Vector3 ObservedVector3::operator*(const ObservedVector3& o) const noexcept {
		return { value.X * o.GetX(), value.Y * o.GetY(), value.Z * o.GetZ() };
	}

	Vector3 ObservedVector3::operator/(const ObservedVector3& o) const noexcept {
		return { value.X / o.GetX(), value.Y / o.GetY(), value.Z / o.GetZ() };
	}

	Vector3 ObservedVector3::operator+(const Vector3& v) const noexcept {
		return { value.X + v.X, value.Y + v.Y, value.Z + v.Z };
	}

	Vector3 ObservedVector3::operator-(const Vector3& v) const noexcept {
		return { value.X - v.X, value.Y - v.Y, value.Z - v.Z };
	}

	ObservedVector3& ObservedVector3::operator+=(const ObservedVector3& o) {
		value += o.value; Notify();
		return *this;
	}

	ObservedVector3& ObservedVector3::operator-=(const ObservedVector3& o) {
		value -= o.value; Notify();
		return *this;
	}

	ObservedVector3& ObservedVector3::operator*=(float scalar) {
		value *= scalar; Notify();
		return *this;
	}

	ObservedVector3& ObservedVector3::operator/=(float scalar) {
		value /= scalar; Notify();
		return *this;
	}

	Vector3 ObservedVector3::operator*(const Vector3& v) const noexcept {
		return Vector3{ value.X * v.X, value.Y * v.Y, value.Z * v.Z };
	}

	Vector3 ObservedVector3::operator/(const Vector3& v) const noexcept {
		return Vector3{ value.X / v.X, value.Y * v.Y, value.Z * v.Z };
	}

	void ObservedVector3::Notify() {
		if (onChange) onChange();
	}
}