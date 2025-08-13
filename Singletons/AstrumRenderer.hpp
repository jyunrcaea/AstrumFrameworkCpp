#pragma once
#include <memory>
#include <queue>
#include <vector>
#include <d3d11.h>
#include <d2d1.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "../AstrumException.hpp"
#include "AstrumSingleton.hpp"
#include "AstrumWindow.hpp"
#include "../Graphics/IAstrumRenderable.hpp"
#include "../Units/AstrumColor.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"
#include "../Vectors/AstrumVector2.hpp"

using Microsoft::WRL::ComPtr;

struct AstrumResolution
{
    unsigned int Width = 0;
    unsigned int Height = 0;
};

struct IAstrumRenderable;

class AstrumRenderer : public AstrumSingleton<AstrumRenderer> {
    friend class AstrumSingleton<AstrumRenderer>;

public:
    uint32_t SampleCount() const;
    // 디바이스와 스왑체인 생성, 뷰포트 설정
    void Initialize(uint16_t width, uint16_t height, bool windowMode = true);
    // 렌더 큐에 있는 그릴수 있는 객체들을 모두 호출하면서 큐를 비우고 스왑체인을 갱신하는 진짜 렌더링 함수.
    void Rendering();

    // 원하는 타입의 버퍼 생성하기
    template<typename T>
    bool CreateBuffer(const std::vector<T>& data,
        ComPtr<ID3D11Buffer>& outBuffer,
        D3D11_BIND_FLAG bind = D3D11_BIND_VERTEX_BUFFER,
        D3D11_USAGE usage = D3D11_USAGE_DEFAULT);

    void Dispose();

    ID3D11Device* GetDevice()  const;
    ID3D11DeviceContext* GetContext() const;

    // 도형 렌더링 시 기본으로 사용할 셰이더
    std::shared_ptr<struct IAstrumShaderSetup> DefaultShapeShaderPipeline = nullptr;
    // 텍스쳐 렌더링 시 기본으로 사용할 셰이더
    std::shared_ptr<struct IAstrumShaderSetup> DefaultTextureShaderPipeline = nullptr;

    // 프레임워크가 제공하는 기본 도형 셰이더를 설정합니다.
    void CreateAndSetDefaultShapePipeline();
    // 프레임워크가 제공하는 기본 머터리얼 셰이더를 설정합니다.
    void CreateAndSetDefaultMaterialPipeline();

    AstrumResolution GetResolution() const;
    AstrumVector2 GetRSRate() const;

private:
    AstrumResolution resolution{};
    UINT sampleCount = 1;

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<IDXGISwapChain> swapChain;
    ComPtr<ID3D11RenderTargetView> renderTargetView;
    ComPtr<ID3D11DepthStencilView> depthStencilView;
    ComPtr<ID3D11DepthStencilState> depthStencilState;
    ComPtr<ID3D11BlendState> blendState;
    ComPtr<ID2D1RenderTarget> renderTarget2D;
	ComPtr<ID2D1Factory> factory2D;
};

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