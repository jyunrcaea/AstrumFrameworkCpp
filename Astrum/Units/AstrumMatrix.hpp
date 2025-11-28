#pragma once
#include <DirectXMath.h>
#include "../Vectors/AstrumVector4.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"

using namespace DirectX;

/// <summary>
/// 4x4 크기의 행렬을 나타내는 구조체입니다.
/// DirectXMath 라이브러리를 기반으로 하여 3D 그래픽스 변환에 사용됩니다.
/// </summary>
struct AstrumMatrix {
    /// <summary>
    /// DirectXMath XMFLOAT4X4 행렬입니다.
    /// </summary>
    XMFLOAT4X4 matrix{};

    /// <summary>
    /// 항등 행렬(Identity matrix)으로 초기화하여 행렬을 생성합니다.
    /// </summary>
    AstrumMatrix() { XMStoreFloat4x4(&matrix, XMMatrixIdentity()); }

    /// <summary>
    /// DirectXMath XMMATRIX로부터 행렬을 생성합니다.
    /// </summary>
    /// <param name="mat">변환할 DirectXMath 행렬입니다.</param>
    AstrumMatrix(const XMMATRIX& mat);

    /// <summary>
    /// 16개의 float 값으로 행렬을 생성합니다.
    /// 행렬의 요소는 행 우선(row-major) 순서로 지정됩니다.
    /// </summary>
    /// <param name="m11">1행 1열 요소입니다.</param>
    /// <param name="m12">1행 2열 요소입니다.</param>
    /// <param name="m13">1행 3열 요소입니다.</param>
    /// <param name="m14">1행 4열 요소입니다.</param>
    /// <param name="m21">2행 1열 요소입니다.</param>
    /// <param name="m22">2행 2열 요소입니다.</param>
    /// <param name="m23">2행 3열 요소입니다.</param>
    /// <param name="m24">2행 4열 요소입니다.</param>
    /// <param name="m31">3행 1열 요소입니다.</param>
    /// <param name="m32">3행 2열 요소입니다.</param>
    /// <param name="m33">3행 3열 요소입니다.</param>
    /// <param name="m34">3행 4열 요소입니다.</param>
    /// <param name="m41">4행 1열 요소입니다.</param>
    /// <param name="m42">4행 2열 요소입니다.</param>
    /// <param name="m43">4행 3열 요소입니다.</param>
    /// <param name="m44">4행 4열 요소입니다.</param>
    AstrumMatrix(
        float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44
    );

    /// <summary>
    /// 지정된 행의 모든 요소를 벡터로 반환합니다.
    /// </summary>
    /// <param name="row">행 인덱스입니다. (0~3)</param>
    /// <returns>해당 행의 벡터입니다.</returns>
    AstrumVector4 GetRow(int row) const;
    /// <summary>
    /// 지정된 행에 벡터를 설정합니다.
    /// </summary>
    /// <param name="row">행 인덱스입니다. (0~3)</param>
    /// <param name="v">설정할 벡터입니다.</param>
    void SetRow(int row, const AstrumVector4& v);
    /// <summary>
    /// 지정된 위치의 행렬 요소를 반환합니다.
    /// </summary>
    /// <param name="x">열 인덱스입니다. (0~3)</param>
    /// <param name="y">행 인덱스입니다. (0~3)</param>
    /// <returns>해당 위치의 값입니다.</returns>
    float Get(int x, int y) const;
    /// <summary>
    /// 지정된 위치의 행렬 요소를 설정합니다.
    /// </summary>
    /// <param name="x">열 인덱스입니다. (0~3)</param>
    /// <param name="y">행 인덱스입니다. (0~3)</param>
    /// <param name="value">설정할 값입니다.</param>
    void Set(int x, int y, float value);

    /// <summary>
    /// 두 행렬을 곱합니다.
    /// </summary>
    /// <param name="other">곱할 행렬입니다.</param>
    /// <returns>곱셈 결과 행렬입니다.</returns>
    AstrumMatrix operator*(const AstrumMatrix& other) const;

    /// <summary>
    /// 행렬을 항등 행렬로 설정합니다.
    /// </summary>
    void SetIdentity();
    /// <summary>
    /// 행렬을 전치합니다. (행과 열을 바꿉니다)
    /// </summary>
    void Transpose();
    /// <summary>
    /// 행렬을 역행렬로 변환합니다.
    /// </summary>
    void Inverse();
    /// <summary>
    /// 행렬을 크기 변환(스케일링) 행렬로 설정합니다. (개별 축)
    /// </summary>
    /// <param name="x">X축 스케일입니다.</param>
    /// <param name="y">Y축 스케일입니다.</param>
    /// <param name="z">Z축 스케일입니다.</param>
    void MakeScaling(float x, float y, float z);
    /// <summary>
    /// 행렬을 회전 행렬로 설정합니다. (개별 축, 도 단위)
    /// </summary>
    /// <param name="xDeg">X축 회전(도)입니다.</param>
    /// <param name="yDeg">Y축 회전(도)입니다.</param>
    /// <param name="zDeg">Z축 회전(도)입니다.</param>
    void MakeRotation(float xDeg, float yDeg, float zDeg);
    /// <summary>
    /// 행렬을 평행 이동 행렬로 설정합니다. (개별 축)
    /// </summary>
    /// <param name="x">X축 이동입니다.</param>
    /// <param name="y">Y축 이동입니다.</param>
    /// <param name="z">Z축 이동입니다.</param>
    void MakeTranslation(float x, float y, float z);

    /// <summary>
    /// 항등 행렬(Identity matrix)입니다.
    /// </summary>
    static const AstrumMatrix Identity;

    /// <summary>
    /// 행렬을 크기 변환(스케일링) 행렬로 설정합니다. (벡터 버전)
    /// </summary>
    /// <param name="v">각 축의 스케일을 포함하는 벡터입니다.</param>
    void MakeScaling(const AstrumVector3& v);
    /// <summary>
    /// 행렬을 회전 행렬로 설정합니다. (벡터 버전, 도 단위)
    /// </summary>
    /// <param name="v">각 축의 회전(도)을 포함하는 벡터입니다.</param>
    void MakeRotation(const AstrumVector3& v);
    /// <summary>
    /// 행렬을 평행 이동 행렬로 설정합니다. (벡터 버전)
    /// </summary>
    /// <param name="v">각 축의 이동을 포함하는 벡터입니다.</param>
    void MakeTranslation(const AstrumVector3& v);
    /// <summary>
    /// 행렬을 크기 변환(스케일링) 행렬로 설정합니다. (관찰 벡터 버전)
    /// </summary>
    /// <param name="v">각 축의 스케일을 포함하는 관찰 벡터입니다.</param>
    void MakeScaling(const AstrumObservedVector3& v);
    /// <summary>
    /// 행렬을 회전 행렬로 설정합니다. (관찰 벡터 버전, 도 단위)
    /// </summary>
    /// <param name="v">각 축의 회전(도)을 포함하는 관찰 벡터입니다.</param>
    void MakeRotation(const AstrumObservedVector3& v);
    /// <summary>
    /// 행렬을 평행 이동 행렬로 설정합니다. (관찰 벡터 버전)
    /// </summary>
    /// <param name="v">각 축의 이동을 포함하는 관찰 벡터입니다.</param>
    void MakeTranslation(const AstrumObservedVector3& v);
};