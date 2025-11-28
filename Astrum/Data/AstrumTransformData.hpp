#pragma once
#include "../Units/AstrumMatrix.hpp"

/// <summary>
/// 렌더링에 필요한 변환 행렬 데이터를 포함하는 구조체입니다.
/// 16바이트 정렬로 Direct3D 상수 버퍼에 최적화되어 있습니다.
/// </summary>
struct alignas(16) AstrumTransformData {
    /// <summary>
    /// 월드 변환 행렬입니다. 로컬 좌표계에서 월드 좌표계로 변환합니다.
    /// </summary>
    AstrumMatrix World;
    /// <summary>
    /// 뷰 변환 행렬입니다. 월드 좌표계에서 카메라 좌표계로 변환합니다.
    /// </summary>
    AstrumMatrix View;
    /// <summary>
    /// 프로젝션 변환 행렬입니다. 카메라 좌표계에서 클립 공간으로 변환합니다.
    /// </summary>
    AstrumMatrix Projection;
    /// <summary>
    /// 월드-뷰 합성 변환 행렬입니다. 로컬 좌표계에서 카메라 좌표계로 직접 변환합니다.
    /// </summary>
    AstrumMatrix WorldView;
    /// <summary>
    /// 월드-뷰-프로젝션 합성 변환 행렬입니다. 로컬 좌표계에서 클립 공간으로 직접 변환합니다.
    /// </summary>
    AstrumMatrix WorldViewProjection;
};