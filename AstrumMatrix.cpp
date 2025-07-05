#include "AstrumMatrix.hpp"

// Define the static identity matrix
const AstrumMatrix AstrumMatrix::Identity = AstrumMatrix();

// Define constructors
AstrumMatrix::AstrumMatrix(const XMMATRIX& mat) {
    XMStoreFloat4x4(&matrix, mat);
}

AstrumMatrix::AstrumMatrix(
    float m11, float m12, float m13, float m14,
    float m21, float m22, float m23, float m24,
    float m31, float m32, float m33, float m34,
    float m41, float m42, float m43, float m44
) {
    matrix = XMFLOAT4X4(
        m11, m12, m13, m14,
        m21, m22, m23, m24,
        m31, m32, m33, m34,
        m41, m42, m43, m44
    );
}

// Define GetRow
AstrumVector4 AstrumMatrix::GetRow(int row) const {
    return AstrumVector4(
        matrix.m[row][0],
        matrix.m[row][1],
        matrix.m[row][2],
        matrix.m[row][3]
    );
}

// Define SetRow
void AstrumMatrix::SetRow(int row, const AstrumVector4& v) {
    matrix.m[row][0] = v.X;
    matrix.m[row][1] = v.Y;
    matrix.m[row][2] = v.Z;
    matrix.m[row][3] = v.W;
}

// Define operator*
AstrumMatrix AstrumMatrix::operator*(const AstrumMatrix& other) const {
    XMMATRIX a = XMLoadFloat4x4(&matrix);
    XMMATRIX b = XMLoadFloat4x4(&other.matrix);
    return AstrumMatrix(XMMatrixMultiply(a, b));
}

// Define other methods
void AstrumMatrix::SetIdentity() {
    XMStoreFloat4x4(&matrix, XMMatrixIdentity());
}

void AstrumMatrix::Transpose() {
    XMStoreFloat4x4(&matrix, XMMatrixTranspose(XMLoadFloat4x4(&matrix)));
}

void AstrumMatrix::Inverse() {
    XMStoreFloat4x4(&matrix, XMMatrixInverse(nullptr, XMLoadFloat4x4(&matrix)));
}

void AstrumMatrix::Scaling(float x, float y, float z) {
    XMStoreFloat4x4(&matrix, XMMatrixScaling(x, y, z));
}

void AstrumMatrix::Rotation(float xDeg, float yDeg, float zDeg) {
    float rx = XMConvertToRadians(xDeg);
    float ry = XMConvertToRadians(yDeg);
    float rz = XMConvertToRadians(zDeg);
    XMStoreFloat4x4(&matrix, XMMatrixRotationRollPitchYaw(rx, ry, rz));
}

void AstrumMatrix::Translation(float x, float y, float z) {
    XMStoreFloat4x4(&matrix, XMMatrixTranslation(x, y, z));
}

void AstrumMatrix::Scaling(const AstrumVector3& v) { Scaling(v.X, v.Y, v.Z); }
void AstrumMatrix::Rotation(const AstrumVector3& v) { Rotation(v.X, v.Y, v.Z); }
void AstrumMatrix::Translation(const AstrumVector3& v) { Translation(v.X, v.Y, v.Z); }
