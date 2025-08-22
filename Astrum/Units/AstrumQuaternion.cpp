#include "AstrumQuaternion.hpp"

namespace Astrum
{
	namespace {
		constexpr float DEG2RAD = static_cast<float>(std::numbers::pi / 180.0);
	}

	Quaternion Quaternion::Identity()
	{
		// 단위 사원수: 회전이 없음
		return Quaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
	}

	Quaternion Quaternion::FromAxisAngle(Vector3 axis, float rad)
	{
		// 축을 정규화
		Vector3 norm = axis.Normalize();
		float halfAngle = rad * 0.5f;
		float sinHalf = std::sin(halfAngle);
		float cosHalf = std::cos(halfAngle);
		return Quaternion{ cosHalf, norm.X * sinHalf, norm.Y * sinHalf, norm.Z * sinHalf };
	}

	Quaternion Quaternion::FromEuler(Vector3 deg)
	{
		// 오일러 각(degree)을 라디안으로 변환
		float roll = deg.X * DEG2RAD;
		float pitch = deg.Y * DEG2RAD;
		float yaw = deg.Z * DEG2RAD;

		float cr = std::cos(roll * 0.5f);
		float sr = std::sin(roll * 0.5f);
		float cp = std::cos(pitch * 0.5f);
		float sp = std::sin(pitch * 0.5f);
		float cy = std::cos(yaw * 0.5f);
		float sy = std::sin(yaw * 0.5f);

		float w = cr * cp * cy + sr * sp * sy;
		float x = sr * cp * cy - cr * sp * sy;
		float y = cr * sp * cy + sr * cp * sy;
		float z = cr * cp * sy - sr * sp * cy;

		return Quaternion{ w, x, y, z };
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		// 사원수 곱셈 공식
		float nw = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
		float nx = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
		float ny = W * rhs.Y - X * rhs.Z + Y * rhs.W + Z * rhs.X;
		float nz = W * rhs.Z + X * rhs.Y - Y * rhs.X + Z * rhs.W;
		return Quaternion{ nw, nx, ny, nz };
	}

	Quaternion Quaternion::operator*(const float scalar) const
	{
		return { W * scalar, X * scalar, Y * scalar, Z * scalar };
	}

	Quaternion& Quaternion::operator*=(float scalar)
	{
		W *= scalar;
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		return *this;
	}

	Vector3 Quaternion::Rotate(const Vector3& v) const
	{
		// 회전을 수행하는 최적화된 방법:
		// v' = v + 2 * cross(q.xyz, cross(q.xyz, v) + q.w * v)
		Vector3 qVec{ X, Y, Z };
		// t = 2 * cross(qVec, v)
		Vector3 t = qVec.Cross(v);
		t.X *= 2.0f; t.Y *= 2.0f; t.Z *= 2.0f;
		// v' = v + q.w * t + cross(qVec, t)
		Vector3 vt = t;
		vt.X *= W; vt.Y *= W; vt.Z *= W;
		Vector3 crossQT = qVec.Cross(t);
		return Vector3{
			v.X + vt.X + crossQT.X,
			v.Y + vt.Y + crossQT.Y,
			v.Z + vt.Z + crossQT.Z
		};
	}

	Quaternion Quaternion::Normalized() const {
		float len = std::sqrt(W * W + X * X + Y * Y + Z * Z);
		return Quaternion{ W / len, X / len, Y / len, Z / len };
	}

	Quaternion Quaternion::Conjugate() const {
		return Quaternion{ W, -X, -Y, -Z };
	}

	Quaternion Quaternion::Inverse() const {
		float len2 = W * W + X * X + Y * Y + Z * Z;
		return Conjugate() * (1.0f / len2);
	}
}
