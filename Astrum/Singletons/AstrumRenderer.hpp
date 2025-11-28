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
#include "../Vectors/AstrumDoubleVector2.hpp"

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
    /// <summary>
    /// 렌더러를 초기화하여 DirectX 디바이스와 스왑체인을 생성하고 뷰포트를 설정합니다.
    /// </summary>
    /// <param name="width">렌더 타겟의 너비(픽셀)입니다.</param>
    /// <param name="height">렌더 타겟의 높이(픽셀)입니다.</param>
    /// <param name="windowMode">창 모드 여부입니다. true이면 창 모드, false이면 전체 화면입니다.</param>
    /// <returns>초기화 성공 여부를 반환합니다.</returns>
    bool Initialize(unsigned int width, unsigned int height, bool windowMode = true);
    /// <summary>
    /// 렌더 큐에 등록된 모든 렌더링 가능한 객체들을 그리고 큐를 비운 후 스왑체인을 갱신합니다.
    /// </summary>
    void Rendering();

    /// <summary>
    /// 지정된 타입의 GPU 버퍼를 생성합니다.
    /// </summary>
    /// <typeparam name="T">버퍼에 저장할 데이터의 타입입니다.</typeparam>
    /// <param name="data">버퍼에 복사할 데이터 벡터입니다.</param>
    /// <param name="outBuffer">생성된 버퍼 포인터를 받을 출력 매개변수입니다.</param>
    /// <param name="bind">버퍼의 바인딩 플래그입니다. 기본값은 정점 버퍼입니다.</param>
    /// <param name="usage">버퍼의 사용 방식입니다. 기본값은 기본 사용법입니다.</param>
    /// <returns>버퍼 생성 성공 여부를 반환합니다.</returns>
    template<typename T>
    bool CreateBuffer(const std::vector<T>& data,
        ComPtr<ID3D11Buffer>& outBuffer,
        D3D11_BIND_FLAG bind = D3D11_BIND_VERTEX_BUFFER,
        D3D11_USAGE usage = D3D11_USAGE_DEFAULT);

    /// <summary>
    /// 렌더러의 모든 리소스를 정리하고 해제합니다.
    /// </summary>
    void Dispose();

    /// <summary>
    /// Direct3D 디바이스 포인터를 반환합니다.
    /// </summary>
    /// <returns>Direct3D 디바이스 포인터입니다.</returns>
    ID3D11Device* GetDevice()  const;
    /// <summary>
    /// Direct3D 디바이스 컨텍스트 포인터를 반환합니다.
    /// </summary>
    /// <returns>Direct3D 디바이스 컨텍스트 포인터입니다.</returns>
    ID3D11DeviceContext* GetContext() const;
    /// <summary>
    /// Direct2D 렌더 타겟 포인터를 반환합니다.
    /// </summary>
    /// <returns>Direct2D 렌더 타겟 포인터입니다.</returns>
	ID2D1RenderTarget* GetRenderTarget2D() const;
    /// <summary>
    /// 깊이-스텐실 뷰 포인터를 반환합니다.
    /// </summary>
    /// <returns>깊이-스텐실 뷰 포인터입니다.</returns>
	ID3D11DepthStencilView* GetDepthStencilView() const;

    // 도형 렌더링 시 기본으로 사용할 셰이더
    std::shared_ptr<struct IAstrumShaderSetup> DefaultShapeShaderPipeline = nullptr;
    // 텍스쳐 렌더링 시 기본으로 사용할 셰이더
    std::shared_ptr<struct IAstrumShaderSetup> DefaultTextureShaderPipeline = nullptr;

    /// <summary>
    /// 프레임워크가 제공하는 기본 도형 렌더링 셰이더 파이프라인을 생성하고 설정합니다.
    /// </summary>
    void CreateAndSetDefaultShapePipeline();
    /// <summary>
    /// 프레임워크가 제공하는 기본 텍스처 렌더링 셰이더 파이프라인을 생성하고 설정합니다.
    /// </summary>
    void CreateAndSetDefaultMaterialPipeline();

    /// <summary>
    /// 현재 렌더 해상도를 반환합니다.
    /// </summary>
    /// <returns>현재 렌더 해상도입니다.</returns>
    AstrumResolution GetResolution() const;
    /// <summary>
    /// 현재 렌더 해상도의 비율을 반환합니다.
    /// </summary>
    /// <returns>렌더 해상도의 비율입니다.</returns>
    AstrumDoubleVector2 GetRSRate() const;
    /// <summary>
    /// 렌더 해상도의 절반 크기를 반환합니다.
    /// </summary>
    /// <returns>렌더 해상도의 절반 크기입니다.</returns>
    AstrumDoubleVector2 GetHalfResolution() const { return { resolution.Width * 0.5, resolution.Height * 0.5 }; }
    /// <summary>
    /// 다중 샘플링 개수를 반환합니다.
    /// </summary>
    /// <returns>다중 샘플링 개수입니다.</returns>
	unsigned int GetSampleCount() const;
private:
    AstrumResolution resolution{};
    unsigned int sampleCount = 1;

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<IDXGISwapChain> swapChain;
    ComPtr<ID3D11RenderTargetView> renderTargetView;
    ComPtr<ID3D11DepthStencilView> depthStencilView;
    ComPtr<ID3D11DepthStencilState> depthStencilState;
    ComPtr<ID3D11BlendState> blendState;
    ComPtr<ID2D1RenderTarget> renderTarget2D;
	ComPtr<ID2D1Factory> factory2D;

	std::shared_ptr<class AstrumRenderTarget> mainRenderTarget = nullptr;
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