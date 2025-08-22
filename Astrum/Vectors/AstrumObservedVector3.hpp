#pragma once

#include "AstrumVector3.hpp"
#include <functional>

namespace Astrum
{
	// x,y,z가 바뀌는걸 감지하는 vector3
	class ObservedVector3 {
	public:
		using Callback = std::function<void()>;

		ObservedVector3(ObservedVector3&& vec3) noexcept;
		// 값이 바뀔때마다 호출되는 함수를 정의할수 있습니다.
		explicit ObservedVector3(const Callback& onChange) noexcept;
		ObservedVector3(float x, float y, float z, const Callback& onChange = {}) noexcept;
		// 이걸 만든 이유는, 크기/회전/좌표가 바뀔때마다
		// 게임 객체가 트리 구조로 되어 있잖아요?
		// 부모가 바뀌면, 자식도 같이 영향을 받아요, 그래서 만약 부모가 스케일을 2로 키우면, 자식은 크기도 2배가 되고, x를 한칸 이동하면 실제로 2칸을 이동해요.
		ObservedVector3(const Vector3& v, const Callback& onChange = {}) noexcept;

		operator Vector3() const noexcept;

		float GetX() const noexcept;
		float GetY() const noexcept;
		float GetZ() const noexcept;

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);

		void AddX(float x);
		void AddY(float y);
		void AddZ(float z);

		void Reset(const Vector3& v);
		void Reset(const ObservedVector3& v);
		// NAN일 경우 기존 값이 할당됩니다.
		void Reset(float x, float y, float z = NAN);

		Vector3 operator+(const ObservedVector3& o) const noexcept;
		Vector3 operator-(const ObservedVector3& o) const noexcept;
		Vector3 operator*(float scalar) const noexcept;
		Vector3 operator/(float scalar) const noexcept;

		Vector3 operator*(const ObservedVector3& o) const noexcept;
		Vector3 operator/(const ObservedVector3& o) const noexcept;

		Vector3 operator+(const Vector3& v) const noexcept;
		Vector3 operator-(const Vector3& v) const noexcept;
		Vector3 operator*(const Vector3& v) const noexcept;
		Vector3 operator/(const Vector3& v) const noexcept;

		ObservedVector3& operator+=(const ObservedVector3& o);
		ObservedVector3& operator-=(const ObservedVector3& o);
		ObservedVector3& operator*=(float scalar);
		ObservedVector3& operator/=(float scalar);

	private:
		Vector3 value{ 0.0f, 0.0f, 0.0f };
		Callback onChange;

		void Notify();
	};
}