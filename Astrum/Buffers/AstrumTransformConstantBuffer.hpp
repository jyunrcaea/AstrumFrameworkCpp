#pragma once
#include <span>
#include <cstddef>
#include "AstrumConstantBuffer.hpp"
#include "../Data/AstrumTransformData.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

/// <summary>
/// 변환 행렬(월드, 뷰, 프로젝션)을 관리하는 상수 버퍼입니다.
/// </summary>
class AstrumTransformConstantBuffer : public AstrumConstantBuffer {
public:
    /// <summary>
    /// 변환 상수 버퍼를 생성합니다.
    /// </summary>
    AstrumTransformConstantBuffer();

    /// <summary>
    /// 월드 변환 행렬입니다.
    /// </summary>
    AstrumMatrix& World = data.World;
    /// <summary>
    /// 뷰 변환 행렬입니다.
    /// </summary>
    AstrumMatrix& View = data.View;
    /// <summary>
    /// 프로젝션 변환 행렬입니다.
    /// </summary>
    AstrumMatrix& Projection = data.Projection;
    /// <summary>
    /// 월드-뷰 합성 변환 행렬입니다.
    /// </summary>
    AstrumMatrix& WorldView = data.WorldView;
    /// <summary>
    /// 월드-뷰-프로젝션 합성 변환 행렬입니다.
    /// </summary>
    AstrumMatrix& WorldViewProjection = data.WorldViewProjection;

    /// <summary>
    /// 상수 버퍼를 업데이트합니다.
    /// </summary>
    virtual void UpdateBuffer() override;

private:
    /// <summary>
    /// 변환 데이터입니다.
    /// </summary>
    AstrumTransformData data{};
};