#include "AstrumObservedVector2.hpp"

namespace Astrum
{
	constexpr ObservedVector2::ObservedVector2() = default;

	ObservedVector2::ObservedVector2(const Callback& onChange)
		: onChange_(onChange) {
	}

	ObservedVector2::ObservedVector2(float x, float y, const Callback& onChange)
		: value_(x, y), onChange_(onChange) {
	}

	ObservedVector2::ObservedVector2(const Vector2& v, const Callback& onChange)
		: value_(v), onChange_(onChange) {
	}

	ObservedVector2::operator Vector2() const {
		return value_;
	}

	float ObservedVector2::GetX() const {
		return value_.X;
	}

	float ObservedVector2::GetY() const {
		return value_.Y;
	}

	void ObservedVector2::SetX(float x) {
		value_.X = x;
		Notify();
	}

	void ObservedVector2::SetY(float y) {
		value_.Y = y;
		Notify();
	}

	void ObservedVector2::Reset(const Vector2& v) {
		value_ = v;
		Notify();
	}

	void ObservedVector2::Reset(float x, float y) {
		value_.X = x;
		value_.Y = y;
		Notify();
	}

	Vector2 ObservedVector2::operator+(const ObservedVector2& o) const {
		return { value_.X + o.value_.X, value_.Y + o.value_.Y };
	}

	Vector2 ObservedVector2::operator-(const ObservedVector2& o) const {
		return { value_.X - o.value_.X, value_.Y - o.value_.Y };
	}

	Vector2 ObservedVector2::operator*(float scalar) const {
		return { value_.X * scalar, value_.Y * scalar };
	}

	Vector2 ObservedVector2::operator/(float scalar) const {
		return { value_.X / scalar, value_.Y / scalar };
	}

	Vector2 ObservedVector2::operator+(const Vector2& v) const {
		return { value_.X + v.X, value_.Y + v.Y };
	}

	Vector2 ObservedVector2::operator-(const Vector2& v) const {
		return { value_.X - v.X, value_.Y - v.Y };
	}

	void ObservedVector2::Notify() {
		if (onChange_) {
			onChange_();
		}
	}

	ObservedVector2& ObservedVector2::operator+=(const ObservedVector2& other) {
		value_.X += other.GetX();
		value_.Y += other.GetY();
		Notify();
		return *this;
	}

	ObservedVector2& ObservedVector2::operator-=(const ObservedVector2& other) {
		value_.X -= other.GetX();
		value_.Y -= other.GetY();
		Notify();
		return *this;
	}

	ObservedVector2& ObservedVector2::operator*=(float scalar) {
		value_.X *= scalar;
		value_.Y *= scalar;
		Notify();
		return *this;
	}

	ObservedVector2& ObservedVector2::operator/=(float scalar) {
		value_.X /= scalar;
		value_.Y /= scalar;
		Notify();
		return *this;
	}
}