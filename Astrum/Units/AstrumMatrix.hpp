#pragma once
#include <DirectXMath.h>
#include "../Vectors/AstrumVector4.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"

namespace Astrum
{
	struct Matrix {
		DirectX::XMFLOAT4X4 matrix{};

		Matrix() { DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixIdentity()); }

		Matrix(const DirectX::XMMATRIX& mat);

		Matrix(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44
		);

		Vector4 GetRow(int row) const;
		void SetRow(int row, const Vector4& v);
		float Get(int x, int y) const;
		void Set(int x, int y, float value);

		Matrix operator*(const Matrix& other) const;

		void SetIdentity();
		void Transpose();
		void Inverse();
		void Scaling(float x, float y, float z);
		void Rotation(float xDeg, float yDeg, float zDeg);
		void Translation(float x, float y, float z);

		static const Matrix Identity;

		void Scaling(const Vector3& v);
		void Rotation(const Vector3& v);
		void Translation(const Vector3& v);
		void Scaling(const ObservedVector3& v);
		void Rotation(const ObservedVector3& v);
		void Translation(const ObservedVector3& v);
	};
}