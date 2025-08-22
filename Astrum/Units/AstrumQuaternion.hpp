#pragma once
#include <numbers>
#include <cmath>
#include "../Vectors/AstrumVector3.hpp"

namespace Astrum
{
	struct Quaternion {
		float W, X, Y, Z;

		static Quaternion Identity();

		static Quaternion FromAxisAngle(Vector3 axis, float rad);
		static Quaternion FromEuler(Vector3 deg);
		Quaternion operator*(const Quaternion& rhs) const;
		Quaternion operator*(float scalar) const;
		Quaternion& operator*=(float scalar);

		Vector3 Rotate(const Vector3& v) const;
		Quaternion Normalized() const;
		Quaternion Conjugate() const;
		Quaternion Inverse() const;
	};
}