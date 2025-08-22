#pragma once
#include "AstrumVector2.hpp"
#include <functional>

namespace Astrum
{
	class ObservedVector2 {
	public:
		using Callback = std::function<void()>;

		constexpr ObservedVector2();
		explicit ObservedVector2(const Callback& onChange);
		ObservedVector2(float x, float y, const Callback& onChange = {});
		ObservedVector2(const Vector2& v, const Callback& onChange = {});

		operator Vector2() const;

		float GetX() const;
		float GetY() const;

		void SetX(float x);
		void SetY(float y);

		void Reset(const Vector2& v);
		void Reset(float x, float y);

		Vector2 operator+(const ObservedVector2& o) const;
		Vector2 operator-(const ObservedVector2& o) const;
		Vector2 operator*(float scalar) const;
		Vector2 operator/(float scalar) const;

		ObservedVector2& operator+=(const ObservedVector2& other);
		ObservedVector2& operator-=(const ObservedVector2& other);
		ObservedVector2& operator*=(float scalar);
		ObservedVector2& operator/=(float scalar);

		Vector2 operator+(const Vector2& v) const;
		Vector2 operator-(const Vector2& v) const;

	private:
		Vector2 value_{ 0.0f, 0.0f };
		Callback onChange_;

		void Notify();
	};
}