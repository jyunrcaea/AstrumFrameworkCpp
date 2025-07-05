#pragma once
#include <bits/stdc++.h> 
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "singleton.hpp"
#include "AstrumWindow.hpp"
#include "AstrumException.hpp"
#include "IAstrumRenderable.hpp"
#include "AstrumColor.hpp"
#include "AstrumShaderPipeline.hpp"

using Microsoft::WRL::ComPtr;

class AstrumRenderer : public singleton<AstrumRenderer> {
    friend class singleton<AstrumRenderer>;

public:
    uint32_t SampleCount() const;

    // 디바이스와 스왑체인 생성, 뷰포트 설정
    void Initialize(uint16_t width, uint16_t height, bool windowMode = true);

    // 렌더링 루프
    void Rendering();

    // 그릴 객체 등록
    void EnqueueRenderable(std::shared_ptr<IAstrumRenderable> renderable);

    // 템플릿 버퍼 생성 (헤더에 구현 필요)
    template<typename T>
    bool CreateBuffer(const std::vector<T>& data,
        ComPtr<ID3D11Buffer>& outBuffer,
        D3D11_BIND_FLAG bind = D3D11_BIND_VERTEX_BUFFER,
        D3D11_USAGE usage = D3D11_USAGE_DEFAULT);

    // 리소스 해제
    void Dispose();

    // 원시 D3D 디바이스/컨텍스트 접근
    ID3D11Device* GetDevice()  const;
    ID3D11DeviceContext* GetContext() const;

    // 현재 사용할 셰이더 파이프라인
    std::shared_ptr<class AstrumShaderPipeline> shaderPipeline = nullptr;

private:
    UINT sampleCount = 1;
    std::queue<std::shared_ptr<IAstrumRenderable>> renderQueue;

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<IDXGISwapChain> swapChain;
    ComPtr<ID3D11RenderTargetView> rtv;
    ComPtr<ID3D11DepthStencilView> dsv;
};

// --- 템플릿 메서드는 헤더에 구현 ---

template<typename T>
bool AstrumRenderer::CreateBuffer(const std::vector<T>& data,
    ComPtr<ID3D11Buffer>& outBuffer,
    D3D11_BIND_FLAG bind,
    D3D11_USAGE usage)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = usage;
    desc.BindFlags = bind;
    desc.ByteWidth = static_cast<UINT>(sizeof(T) * data.size());
    desc.CPUAccessFlags = (usage == D3D11_USAGE_DYNAMIC)
        ? D3D11_CPU_ACCESS_WRITE
        : (usage == D3D11_USAGE_STAGING)
        ? (D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ)
        : 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data.data();

    return SUCCEEDED(device->CreateBuffer(&desc, &initData, &outBuffer));
}