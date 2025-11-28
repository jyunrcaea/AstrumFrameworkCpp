#pragma once
#include <memory>
#include <d3d11.h>

/// <summary>
/// Direct3D 상수 버퍼를 관리하는 인터페이스입니다.
/// </summary>
struct IAstrumConstantBuffer {
    /// <summary>
    /// IAstrumConstantBuffer 인터페이스를 소멸합니다.
    /// </summary>
    virtual ~IAstrumConstantBuffer() = default;
    /// <summary>
    /// Direct3D 상수 버퍼 포인터를 반환합니다.
    /// </summary>
    /// <returns>상수 버퍼 포인터입니다.</returns>
    virtual ID3D11Buffer* GetConstantBuffer() const = 0;
    /// <summary>
    /// 상수 버퍼의 내용을 업데이트합니다.
    /// </summary>
    virtual void UpdateBuffer() = 0;
};