#include "AstrumRenderer.hpp"
#include "../Shaders/AstrumShaderSetup.hpp"
#include "AstrumRenderQueue.hpp"
#include "../Shaders/AstrumDefaultShaders.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include <algorithm>
#include <cmath>

bool AstrumRenderer::Initialize(unsigned int width, unsigned int height, bool windowMode) {
    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

#pragma region Create device and context
    D3D_FEATURE_LEVEL featureLevel;
    if (FAILED(D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
        nullptr, 0, D3D11_SDK_VERSION,
        &device, &featureLevel, &context
    ))) {
        AstrumException("Direct3D11 device creating failed.").Alert();
        return false;
    }
#pragma endregion

    // 게임 화면의 논리 해상도. 창 크기가 바뀌어도 유지되며, 화면은 비율을 유지한 채 창에 맞춰 확대/축소됩니다.
    resolution.Width = width;
    resolution.Height = height;

    // 백버퍼는 창의 실제 클라이언트 영역 크기로 만듭니다. (창 크기가 바뀌면 Resize()에서 다시 맞춤)
    const auto clientSize = AstrumWindow::GetClientSize();
    const UINT backWidth = clientSize.Width > 0 ? static_cast<UINT>(clientSize.Width) : width;
    const UINT backHeight = clientSize.Height > 0 ? static_cast<UINT>(clientSize.Height) : height;

#pragma region Create swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = backWidth;
    swapChainDesc.BufferDesc.Height = backHeight;
    // Use a D2D1-compatible backbuffer format (no sRGB) for CreateDxgiSurfaceRenderTarget.
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    // 창 모드에서는 주사율이 무시되고, 전체 화면에서는 0/1로 두면 DXGI가 모니터에 맞는 값을 고릅니다. (특정 모니터 값을 하드코딩하지 않음)
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    // MSAA must be 1 for D2D to render on the DXGI surface.
    sampleCount = 1;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = AstrumWindow::GetHandle();
    swapChainDesc.Windowed = windowMode;
    // currently, I don't use flip model, because it is required vsync.
#if _WIN32_WINNT >= 0x0603 && FALSE
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.SampleDesc.Count = sampleCount = 1;
#else
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.BufferCount = 1;
#endif

    ComPtr<IDXGIDevice> dxgiDevice;
    ComPtr<IDXGIAdapter> adapter;
    ComPtr<IDXGIFactory>  factory;
    device.As(&dxgiDevice);
    dxgiDevice->GetAdapter(&adapter);
    adapter->GetParent(IID_PPV_ARGS(&factory));

    if (FAILED(factory->CreateSwapChain(device.Get(), &swapChainDesc, &swapChain))) {
        AstrumException("Swap chain creating failed.").Alert();
        return false;
    }
#pragma endregion

#pragma region Create depth stencil state
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = TRUE;
    // 깊이를 기록해서 Position.Z가 앞뒤 순서를 결정하도록 합니다. (Z가 작을수록 앞)
    // 투명한 픽셀이 깊이 버퍼를 덮어써서 뒤의 물체가 사라지던 문제는 기본 픽셀 셰이더에서 clip()으로 버려서 해결합니다.
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    // 같은 Z끼리는 나중에 그려진 물체(자식 목록에서 뒤에 추가된 물체)가 위에 보이도록 LESS_EQUAL을 사용합니다.
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    dsDesc.StencilEnable = FALSE;
    if (FAILED(device->CreateDepthStencilState(&dsDesc, &depthStencilState))) {
        AstrumException("Create depth stencil state failed.").Alert();
        return false;
    }
    // 깊이 검사는 하되 기록하지 않는 상태 (포스트 프로세스 합성처럼 화면 전체를 덮는 그리기에 사용)
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    if (FAILED(device->CreateDepthStencilState(&dsDesc, &depthStencilStateNoWrite))) {
        AstrumException("Create depth stencil state failed.").Alert();
        return false;
    }
#pragma endregion

#pragma region Create blend state
    D3D11_BLEND_DESC blendDescription{};
    blendDescription.RenderTarget[0].BlendEnable = true;
    //blendDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    blendDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    // 알파 마스크를 만들텐데, 투명한 물체의 외곽선을 부드럽게
    //blendDescription.AlphaToCoverageEnable = true; // 라기에는 투명도를 잘 표현하지 못하는 문제가 생기므로 취소.
    // 여러개의 렌더 타겟에서 각각 다른 블렌딩 설정을 쓸지
    blendDescription.IndependentBlendEnable = false;
    if (FAILED(device->CreateBlendState(&blendDescription, &blendState))) {
        AstrumException("Failed to create blend state.").Alert();
        return false;
    }
#pragma endregion

#pragma region Initialize 2D factory
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, factory2D.GetAddressOf()))) {
        AstrumException("Failed to create D2D factory.").Alert();
        return false;
    }
#pragma endregion

    // 백버퍼 크기에 의존하는 리소스 (렌더 타겟 뷰, 깊이 버퍼, D2D 렌더 타겟, 뷰포트)
    if (false == CreateSizeDependentResources(backWidth, backHeight)) return false;

	mainRenderTarget = AstrumRenderTarget::MakeShared(width, height);

    AstrumTextureSampler::Initialize();
    AstrumTextureSampler::SetSampler(AstrumTextureSampleType_Linear);

    CreateAndSetDefaultShapePipeline();
    CreateAndSetDefaultMaterialPipeline();

    return true;
}

void AstrumRenderer::Rendering() {
    AstrumRenderQueue::PeekToPreRender();

    const auto& c = AstrumWindow::BackgroundColor();
    float bg[4] = { c.Red, c.Green, c.Blue, c.Alpha };

    // 백버퍼 전체(레터박스 영역 포함)를 배경색으로 지웁니다.
    context->ClearRenderTargetView(renderTargetView.Get(), bg);
    context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
    // 논리 해상도의 비율을 유지하는 뷰포트
    context->RSSetViewports(1, &viewport);
    // DepthStencilState 바인딩
    context->OMSetDepthStencilState(depthStencilState.Get(), 1);

    // 이전 블렌딩 백업 (OMGetBlendState는 참조 카운트를 올리므로 ComPtr로 받아서 해제되도록 함)
    ComPtr<ID3D11BlendState> prevBlendState;
    float prevBlendFactor[4];
    unsigned int prevSampleMask;
    context->OMGetBlendState(prevBlendState.GetAddressOf(), prevBlendFactor, &prevSampleMask);

    renderTarget2D->BeginDraw(); // D2D 렌더링 시작 (알파 블렌딩 덮어씌워지니 먼저 호출)
    // D2D 좌표(논리 해상도)를 뷰포트에 맞춰 확대/이동합니다.
    renderTarget2D->SetTransform(
        D2D1::Matrix3x2F::Scale(viewportScale, viewportScale) *
        D2D1::Matrix3x2F::Translation(viewport.TopLeftX, viewport.TopLeftY)
    );

    // 알파 블렌딩 켜기
    float blendFactor[4] = { 0,0,0,0 };
    UINT  sampleMask = 0xFFFFFFFF;
    context->OMSetBlendState(blendState.Get(), blendFactor, sampleMask);

	AstrumRenderQueue::DequeueToRender(); // 실제 드로우 콜 처리
    renderTarget2D->EndDraw(); // D2D 렌더링 종료

    // 이전 블렌딩 돌려놓기
    context->OMSetBlendState(prevBlendState.Get(), prevBlendFactor, prevSampleMask);

    // 진짜 출력 (수직 동기화가 켜져 있으면 모니터 주사율에 맞춰 대기)
    swapChain->Present(vsync ? 1 : 0, 0);
}

void AstrumRenderer::Dispose() {
    // There are not handle something, because ComPtr
    AstrumTextureSampler::Dispose(); // Same. Just for design.
	AstrumRenderQueue::Dispose();
}

ID3D11Device* AstrumRenderer::GetDevice() const { return device.Get(); }
ID3D11DeviceContext* AstrumRenderer::GetContext() const { return context.Get(); }
ID2D1RenderTarget* AstrumRenderer::GetRenderTarget2D() const { return renderTarget2D.Get(); }
ID3D11DepthStencilView* AstrumRenderer::GetDepthStencilView() const { return depthStencilView.Get(); }

void AstrumRenderer::CreateAndSetDefaultShapePipeline() {
    AstrumRenderer::Instance().DefaultShapeShaderPipeline = AstrumDefaultShaders::CreateShapeShaderSetup();
}

void AstrumRenderer::CreateAndSetDefaultMaterialPipeline() {
    AstrumRenderer::Instance().DefaultTextureShaderPipeline = AstrumDefaultShaders::CreateMaterialShaderSetup();
}

AstrumResolution AstrumRenderer::GetResolution() const {
    return resolution;
}

AstrumDoubleVector2 AstrumRenderer::GetRSRate() const {
    // 화면은 비율을 유지한 채 확대/축소되므로 두 축의 비율은 같습니다.
    const double rate = viewportScale > 0.0f ? 1.0 / static_cast<double>(viewportScale) : 1.0;
    return AstrumDoubleVector2{ rate, rate };
}

AstrumDoubleVector2 AstrumRenderer::ClientToResolution(double clientX, double clientY) const {
    const double scale = viewportScale > 0.0f ? static_cast<double>(viewportScale) : 1.0;
    return AstrumDoubleVector2{
        (clientX - viewport.TopLeftX) / scale,
        static_cast<double>(resolution.Height) - (clientY - viewport.TopLeftY) / scale
    };
}

void AstrumRenderer::SetDepthWriteEnabled(bool enable) {
    context->OMSetDepthStencilState((enable ? depthStencilState : depthStencilStateNoWrite).Get(), 1);
}

void AstrumRenderer::Resize(unsigned int clientWidth, unsigned int clientHeight) {
    // 초기화 전이거나(창 생성 중의 WM_SIZE) 최소화된 경우는 무시합니다.
    if (nullptr == swapChain || 0 == clientWidth || 0 == clientHeight) return;
    if (clientWidth == backBufferWidth && clientHeight == backBufferHeight) return;

    // 백버퍼를 참조하는 모든 리소스를 해제해야 ResizeBuffers가 성공합니다.
    context->OMSetRenderTargets(0, nullptr, nullptr);
    renderTargetView.Reset();
    depthStencilView.Reset();
    renderTarget2D.Reset();
    context->Flush();

    if (FAILED(swapChain->ResizeBuffers(0, clientWidth, clientHeight, DXGI_FORMAT_UNKNOWN, 0))) {
        AstrumException("Failed to resize swap chain buffers.").Alert();
        return;
    }
    CreateSizeDependentResources(clientWidth, clientHeight);
}

bool AstrumRenderer::CreateSizeDependentResources(unsigned int width, unsigned int height) {
#pragma region Create render target view
    ComPtr<ID3D11Texture2D> backBuffer;
    if (FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)))) {
        AstrumException("Get buffer from swap chain failed.").Alert();
        return false;
    }

    if (FAILED(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView))) {
        AstrumException("Render target view creating failed.").Alert();
        return false;
    }
#pragma endregion

#pragma region Create depth buffer and depth stencil view
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    ComPtr<ID3D11Texture2D> depthBuffer;
    if (FAILED(device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer))) {
        AstrumException("Create depth buffer failed.").Alert();
        return false;
    }
    if (FAILED(device->CreateDepthStencilView(depthBuffer.Get(), nullptr, &depthStencilView))) {
        AstrumException("Create depth stencil view failed.").Alert();
        return false;
    }
#pragma endregion

#pragma region Create 2D render target
    ComPtr<IDXGISurface> backSurface;
    if (FAILED(backBuffer.As(&backSurface))) {
        AstrumException("Failed to get DXGI surface from back buffer.").Alert();
        return false;
    }
    // DPI를 96으로 고정해서 D2D 좌표 1이 픽셀 1이 되도록 합니다. (확대/축소는 Rendering()의 변환 행렬로 처리)
    if (FAILED(factory2D->CreateDxgiSurfaceRenderTarget(
        backSurface.Get(),
        D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96.0f, 96.0f),
        renderTarget2D.GetAddressOf()
    ))) {
        AstrumException("Failed to create D2D render target.").Alert();
        return false;
    }
    // D2D 렌더 타겟이 새로 만들어졌으므로, 이전 렌더 타겟으로 만든 브러시 등은 다시 만들어야 합니다.
    ++renderTarget2DVersion;
#pragma endregion

    backBufferWidth = width;
    backBufferHeight = height;
    UpdateViewport();
    return true;
}

void AstrumRenderer::UpdateViewport() {
    // 논리 해상도의 비율을 유지하면서 백버퍼에 가장 크게 들어가는 크기 (남는 부분은 레터박스)
    const float scaleX = static_cast<float>(backBufferWidth) / static_cast<float>(resolution.Width);
    const float scaleY = static_cast<float>(backBufferHeight) / static_cast<float>(resolution.Height);
    viewportScale = (std::min)(scaleX, scaleY);

    viewport = {};
    viewport.Width = static_cast<float>(resolution.Width) * viewportScale;
    viewport.Height = static_cast<float>(resolution.Height) * viewportScale;
    viewport.TopLeftX = std::floor((static_cast<float>(backBufferWidth) - viewport.Width) * 0.5f);
    viewport.TopLeftY = std::floor((static_cast<float>(backBufferHeight) - viewport.Height) * 0.5f);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);
}

unsigned int AstrumRenderer::GetSampleCount() const { return sampleCount; }
