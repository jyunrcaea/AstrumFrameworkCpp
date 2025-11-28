#pragma once
#include <wrl/client.h>
#include <vector>
#include <span>
#include <cstdint>
#include <cstring>
#include "IAstrumConstantBuffer.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

class AstrumConstantBuffer : public IAstrumConstantBuffer {
public:
    /// <summary>
    /// 지정된 크기의 상수 버퍼를 생성합니다.
    /// </summary>
    /// <param name="size">버퍼의 크기(바이트)입니다.</param>
     AstrumConstantBuffer(unsigned int size);
    /// <summary>
    /// 상수 버퍼를 소멸합니다.
    /// </summary>
    virtual ~AstrumConstantBuffer() override;
    /// <summary>
    /// 상수 버퍼의 리소스를 정리하고 해제합니다.
    /// </summary>
    virtual void Dispose();
    /// <summary>
    /// Direct3D 상수 버퍼 포인터를 반환합니다.
    /// </summary>
    /// <returns>상수 버퍼 포인터입니다.</returns>
    ID3D11Buffer* GetConstantBuffer() const override;
    /// <summary>
    /// 상수 버퍼의 크기를 반환합니다.
    /// </summary>
    /// <returns>버퍼의 크기(바이트)입니다.</returns>
    unsigned int GetBufferSize() const;

    /// <summary>
    /// 상수 버퍼의 내용을 업데이트합니다. 파생 클래스에서 구현해야 합니다.
    /// </summary>
    virtual void UpdateBuffer() override = 0;

    /// <summary>
    /// 지정된 데이터를 상수 버퍼에 복사합니다.
    /// </summary>
    /// <typeparam name="T">버퍼에 복사할 데이터의 타입입니다.</typeparam>
    /// <param name="data">버퍼에 복사할 데이터입니다.</param>
	template<typename T>
	void UpdateConstantBuffer(T& data);
    /// <summary>
    /// 상수 버퍼를 픽셀 셰이더에 바인딩합니다.
    /// </summary>
    /// <param name="slot">바인딩할 상수 버퍼 슬롯 번호입니다.</param>
    void SetPixelShaderConstantBuffer(unsigned int slot);
    /// <summary>
    /// 상수 버퍼를 정점 셰이더에 바인딩합니다.
    /// </summary>
    /// <param name="slot">바인딩할 상수 버퍼 슬롯 번호입니다.</param>
    void SetVertexShaderConstantBuffer(unsigned int slot);
    /// <summary>
    /// 상수 버퍼를 기하 셰이더에 바인딩합니다.
    /// </summary>
    /// <param name="slot">바인딩할 상수 버퍼 슬롯 번호입니다.</param>
    void SetGeometryShaderConstantBuffer(unsigned int slot);
    /// <summary>
    /// 상수 버퍼를 헐 셰이더에 바인딩합니다.
    /// </summary>
    /// <param name="slot">바인딩할 상수 버퍼 슬롯 번호입니다.</param>
    void SetHullShaderConstantBuffer(unsigned int slot);
    /// <summary>
    /// 상수 버퍼를 도메인 셰이더에 바인딩합니다.
    /// </summary>
    /// <param name="slot">바인딩할 상수 버퍼 슬롯 번호입니다.</param>
    void SetDomainShaderConstantBuffer(unsigned int slot);
    /// <summary>
    /// 상수 버퍼를 컴퓨트 셰이더에 바인딩합니다.
    /// </summary>
    /// <param name="slot">바인딩할 상수 버퍼 슬롯 번호입니다.</param>
    void SetComputeShaderConstantBuffer(unsigned int slot);

protected:
    /// <summary>
    /// 지정된 데이터로 상수 버퍼를 업데이트합니다.
    /// </summary>
    /// <param name="data">버퍼에 복사할 바이트 데이터입니다.</param>
    void Update(std::span<const std::byte> data);
    /// <summary>
    /// Direct3D 상수 버퍼입니다.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    /// <summary>
    /// 상수 버퍼의 크기(바이트)입니다.
    /// </summary>
    const unsigned int bufferSize;
};

template<typename T>
inline void AstrumConstantBuffer::UpdateConstantBuffer(T& data) {
	Update(std::as_bytes(std::span{ &data, 1 }));
}