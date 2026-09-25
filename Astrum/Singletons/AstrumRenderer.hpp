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
    /// <param name="width">게임 화면의 논리 해상도 너비(픽셀)입니다. 창 크기가 바뀌어도 유지됩니다.</param>
    /// <param name="height">게임 화면의 논리 해상도 높이(픽셀)입니다. 창 크기가 바뀌어도 유지됩니다.</param>
    /// <param name="windowMode">창 모드 여부입니다. true이면 창 모드, false이면 전체 화면입니다.</param>
    /// <returns>초기화 성공 여부를 반환합니다.</returns>
    bool Initialize(unsigned int width, unsigned int height, bool windowMode = true);
    /// <summary>
    /// 렌더 큐에 등록된 모든 렌더링 가능한 객체들을 그리고 큐를 비운 후 스왑체인을 갱신합니다.
    /// </summary>
    void Rendering();
    /// <summary>
    /// 창의 클라이언트 영역 크기가 바뀌었을 때 백버퍼 크기를 맞춥니다. (AstrumWindow가 WM_SIZE에서 호출)
    /// 논리 해상도는 유지되며, 화면은 비율을 유지한 채 확대/축소되고 남는 영역은 배경색으로 채워집니다.
    /// </summary>
    /// <param name="clientWidth">클라이언트 영역 너비(픽셀)</param>
    /// <param name="clientHeight">클라이언트 영역 높이(픽셀)</param>
    void Resize(unsigned int clientWidth, unsigned int clientHeight);

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
    /// 클라이언트 영역 1픽셀당 논리 해상도 단위의 비율을 반환합니다. (비율을 유지하며 확대/축소되므로 X, Y가 같습니다.)
    /// </summary>
    /// <returns>렌더 해상도의 비율입니다.</returns>
    AstrumDoubleVector2 GetRSRate() const;
    /// <summary>
    /// 클라이언트 영역 좌표(왼쪽 위 원점, 픽셀)를 논리 해상도 좌표(왼쪽 아래 원점)로 변환합니다. (레터박스 여백과 확대/축소를 반영)
    /// </summary>
    AstrumDoubleVector2 ClientToResolution(double clientX, double clientY) const;
    /// <summary>
    /// 이후 그리기의 깊이 기록 여부를 설정합니다. (깊이 검사는 항상 수행됩니다.)
    /// 화면 전체를 덮는 합성처럼 깊이를 기록하면 안 되는 그리기에 사용하고, 끝나면 다시 true로 되돌려야 합니다.
    /// </summary>
    void SetDepthWriteEnabled(bool enable);
    /// <summary>
    /// D2D 렌더 타겟이 (창 크기 변경 등으로) 다시 만들어질 때마다 증가하는 값입니다.
    /// 이전 렌더 타겟으로 만든 D2D 리소스(브러시 등)는 이 값이 바뀌면 다시 만들어야 합니다.
    /// </summary>
    unsigned int GetRenderTarget2DVersion() const { return renderTarget2DVersion; }
    /// <summary>
    /// 렌더 해상도의 절반 크기를 반환합니다.
    /// </summary>
    /// <returns>렌더 해상도의 절반 크기입니다.</returns>
    AstrumDoubleVector2 GetHalfResolution() const { return { resolution.Width * 0.5, resolution.Height * 0.5 }; }
    /// <summary>
    /// 수직 동기화(VSync) 사용 여부를 설정합니다. 켜면 화면 출력이 모니터 주사율에 맞춰지며, 대기하는 동안 CPU를 사용하지 않습니다. (기본값: false)
    /// </summary>
    void SetVSync(bool enable) { vsync = enable; }
    /// <summary>
    /// 수직 동기화(VSync) 사용 여부를 반환합니다.
    /// </summary>
    bool IsVSync() const { return vsync; }
    /// <summary>
    /// 다중 샘플링 개수를 반환합니다.
    /// </summary>
    /// <returns>다중 샘플링 개수입니다.</returns>
	unsigned int GetSampleCount() const;
private:
    AstrumResolution resolution{};
    unsigned int sampleCount = 1;
    bool vsync = false;

    // 백버퍼(=클라이언트 영역) 크기
    unsigned int backBufferWidth = 0;
    unsigned int backBufferHeight = 0;
    // 논리 해상도를 비율 유지하며 백버퍼에 맞춘 뷰포트와 그 배율
    D3D11_VIEWPORT viewport{};
    float viewportScale = 1.0f;
    unsigned int renderTarget2DVersion = 0;

    // 백버퍼 크기에 의존하는 리소스(렌더 타겟 뷰, 깊이 버퍼, D2D 렌더 타겟)를 만들고 뷰포트를 갱신합니다.
    bool CreateSizeDependentResources(unsigned int width, unsigned int height);
    void UpdateViewport();

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<IDXGISwapChain> swapChain;
    ComPtr<ID3D11RenderTargetView> renderTargetView;
    ComPtr<ID3D11DepthStencilView> depthStencilView;
    ComPtr<ID3D11DepthStencilState> depthStencilState;
    ComPtr<ID3D11DepthStencilState> depthStencilStateNoWrite;
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