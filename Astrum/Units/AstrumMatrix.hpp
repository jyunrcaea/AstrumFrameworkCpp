#pragma once
#include <DirectXMath.h>
#include "../Vectors/AstrumVector4.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"

using namespace DirectX;

struct AstrumMatrix {
    XMFLOAT4X4 matrix{};

    AstrumMatrix() { XMStoreFloat4x4(&matrix, XMMatrixIdentity()); }

    AstrumMatrix(const XMMATRIX& mat);

    AstrumMatrix(
        float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44
    );

    AstrumVector4 GetRow(int row) const;
    void SetRow(int row, const AstrumVector4& v);
    float Get(int x, int y) const;
    void Set(int x, int y, float value);

    AstrumMatrix operator*(const AstrumMatrix& other) const;

    void SetIdentity();
    void Transpose();
    void Inverse();
    void Scaling(float x, float y, float z);
    void Rotation(float xDeg, float yDeg, float zDeg);
    void Translation(float x, float y, float z);

    static const AstrumMatrix Identity;

    void Scaling(const AstrumVector3& v);
    void Rotation(const AstrumVector3& v);
    void Translation(const AstrumVector3& v);
    void Scaling(const AstrumObservedVector3& v);
    void Rotation(const AstrumObservedVector3& v);
    void Translation(const AstrumObservedVector3& v);
};