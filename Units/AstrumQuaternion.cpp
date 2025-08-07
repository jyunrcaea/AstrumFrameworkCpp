#include "AstrumQuaternion.hpp"

namespace {
	constexpr float DEG2RAD = static_cast<float>(std::numbers::pi / 180.0);
}

AstrumQuaternion AstrumQuaternion::Identity()
{
    // 단위 사원수: 회전이 없음
    return AstrumQuaternion{1.0f, 0.0f, 0.0f, 0.0f};
}

AstrumQuaternion AstrumQuaternion::FromAxisAngle(AstrumVector3 axis, float rad)
{
    // 축을 정규화
    AstrumVector3 norm = axis.Normalize();
    float halfAngle = rad * 0.5f;
    float sinHalf = std::sin(halfAngle);
    float cosHalf = std::cos(halfAngle);
    return AstrumQuaternion{cosHalf, norm.X * sinHalf, norm.Y * sinHalf, norm.Z * sinHalf};
}

AstrumQuaternion AstrumQuaternion::FromEuler(AstrumVector3 deg)
{
    // 오일러 각(degree)을 라디안으로 변환
    float roll  = deg.X * DEG2RAD;
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
    
    return AstrumQuaternion{w, x, y, z};
}

AstrumQuaternion AstrumQuaternion::operator*(const AstrumQuaternion& rhs) const
{
    // 사원수 곱셈 공식
    float nw = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
    float nx = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
    float ny = W * rhs.Y - X * rhs.Z + Y * rhs.W + Z * rhs.X;
    float nz = W * rhs.Z + X * rhs.Y - Y * rhs.X + Z * rhs.W;
    return AstrumQuaternion{nw, nx, ny, nz};
}

AstrumQuaternion AstrumQuaternion::operator*(const float scalar) const
{
    return { W * scalar, X * scalar, Y * scalar, Z * scalar };
}

AstrumQuaternion& AstrumQuaternion::operator*=(float scalar)
{
	W *= scalar;
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
    return *this;
}

AstrumVector3 AstrumQuaternion::Rotate(const AstrumVector3& v) const
{
    // 회전을 수행하는 최적화된 방법:
    // v' = v + 2 * cross(q.xyz, cross(q.xyz, v) + q.w * v)
    AstrumVector3 qVec{X, Y, Z};
    // t = 2 * cross(qVec, v)
    AstrumVector3 t = qVec.Cross(v);
    t.X *= 2.0f; t.Y *= 2.0f; t.Z *= 2.0f;
    // v' = v + q.w * t + cross(qVec, t)
    AstrumVector3 vt = t;
    vt.X *= W; vt.Y *= W; vt.Z *= W;
    AstrumVector3 crossQT = qVec.Cross(t);
    return AstrumVector3{
        v.X + vt.X + crossQT.X,
        v.Y + vt.Y + crossQT.Y,
        v.Z + vt.Z + crossQT.Z
    };
}

AstrumQuaternion AstrumQuaternion::Normalized() const {
    float len = std::sqrt(W * W + X * X + Y * Y + Z * Z);
    return AstrumQuaternion{ W / len, X / len, Y / len, Z / len };
}

AstrumQuaternion AstrumQuaternion::Conjugate() const {
    return AstrumQuaternion{ W, -X, -Y, -Z };
}

AstrumQuaternion AstrumQuaternion::Inverse() const {
    float len2 = W * W + X * X + Y * Y + Z * Z;
    return Conjugate() * (1.0f / len2);
}
