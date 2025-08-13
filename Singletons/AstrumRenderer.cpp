#include "AstrumRenderer.hpp"
#include "../Shaders/AstrumShaderSetup.hpp"
#include "AstrumRenderQueue.hpp"

void AstrumRenderer::Initialize(uint16_t width, uint16_t height, bool windowMode) {
    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    if (FAILED(D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
        nullptr, 0, D3D11_SDK_VERSION,
        &device, &featureLevel, &context)))
    {
        throw AstrumException("Direct3D11 device creating failed.");
    }

    // 멀티샘플링 지원 확인
    for (UINT p = 8; p > 1; p >>= 1) {
        UINT quality;
        if (SUCCEEDED(device->CheckMultisampleQualityLevels(
            DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, p, &quality)) && quality > 0)
        {
            sampleCount = p;
            break;
        }
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.SampleDesc.Count = sampleCount;
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
    ComPtr<IDXGIAdapter>  adapter;
    ComPtr<IDXGIFactory>  factory;
    device.As(&dxgiDevice);
    dxgiDevice->GetAdapter(&adapter);
    adapter->GetParent(IID_PPV_ARGS(&factory));

    if (FAILED(factory->CreateSwapChain(device.Get(), &swapChainDesc, &swapChain))) {
        throw AstrumException("Swap chain creating failed.");
    }

    ComPtr<ID3D11Texture2D> backBuffer;
    if (FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)))) {
        throw AstrumException("Get buffer from swap chain failed.");
    }

    if (FAILED(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView))) {
        throw AstrumException("Render target view creating failed.");
    }

    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = sampleCount;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    ComPtr<ID3D11Texture2D> depthBuffer;
    if (FAILED(device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer))) {
        throw AstrumException("Create depth buffer failed.");
    }
    if (FAILED(device->CreateDepthStencilView(depthBuffer.Get(), nullptr, &depthStencilView))) {
        throw AstrumException("Create depth stencil view failed.");
    }

    // DepthStencilState 생성
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    dsDesc.StencilEnable = FALSE;
    if (FAILED(device->CreateDepthStencilState(&dsDesc, &depthStencilState))) {
        throw AstrumException("Create depth stencil state failed.");
    }

    // BlendState 생성
    D3D11_BLEND_DESC blendDescription{};
    blendDescription.RenderTarget[0].BlendEnable = true;
    blendDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    // 알파 마스크를 만들텐데, 투명한 물체의 외곽선을 부드럽게
    blendDescription.AlphaToCoverageEnable = true;
    // 여러개의 렌더 타겟에서 각각 다른 블렌딩 설정을 쓸지
    blendDescription.IndependentBlendEnable = false;
    if (FAILED(device->CreateBlendState(&blendDescription, &blendState)))
        throw AstrumException("Failed to create blend state.");

    resolution.Width = width;
    resolution.Height = height;
    // Viewport
    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);

	// Direct2D 초기화
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, factory2D.GetAddressOf()))) {
        throw AstrumException("Failed to create D2D factory.");
	}

	ComPtr<IDXGISurface> backSurface;
	swapChain->GetBuffer(0, IID_PPV_ARGS(&backSurface));
	if (FAILED(factory2D->CreateDxgiSurfaceRenderTarget(
		backSurface.Get(),
        D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
        renderTarget2D.GetAddressOf()
	))) throw AstrumException("Failed to create D2D render target.");

    AstrumTextureSampler::Instance().Initialize();
    AstrumTextureSampler::Instance().SetSampler(AstrumTextureSampleType_Linear);

    CreateAndSetDefaultShapePipeline();
    CreateAndSetDefaultMaterialPipeline();
}

void AstrumRenderer::Rendering() {
    AstrumRenderQueue::PeekToPreRender();

    const auto& c = AstrumWindow::BackgroundColor();
    float bg[4] = { c.Red, c.Green, c.Blue, c.Alpha };

    context->ClearRenderTargetView(renderTargetView.Get(), bg);
    context->ClearDepthStencilView(depthStencilView.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
    // DepthStencilState 바인딩
    context->OMSetDepthStencilState(depthStencilState.Get(), 1);
    // 이전 블렌딩 백업
    ID3D11BlendState* prevBlendState;
    float prevBlendFactor[4];
    unsigned int prevSampleMask;
    context->OMGetBlendState(&prevBlendState, prevBlendFactor, &prevSampleMask);
    // 알파 블렌딩 켜기
    float blendFactor[4] = { 0,0,0,0 };
    UINT  sampleMask = 0xFFFFFFFF;
    context->OMSetBlendState(blendState.Get(), blendFactor, sampleMask);
    // 실제 드로우 콜 처리
	AstrumRenderQueue::DequeueToRender();
    // 이전 블렌딩 돌려놓기
    context->OMSetBlendState(prevBlendState, prevBlendFactor, prevSampleMask);
    // 진짜 출력
    swapChain->Present(0, 0);
}

void AstrumRenderer::Dispose() {
    // There are not handle something, because ComPtr
    AstrumTextureSampler::Instance().Dispose(); // Same. Just for design.
	AstrumRenderQueue::Dispose();
}

ID3D11Device* AstrumRenderer::GetDevice() const { return device.Get(); }
ID3D11DeviceContext* AstrumRenderer::GetContext() const { return context.Get(); }
ID2D1RenderTarget* AstrumRenderer::GetRenderTarget2D() const { return renderTarget2D.Get(); }

void AstrumRenderer::CreateAndSetDefaultShapePipeline() {
    auto shapePipeline = AstrumShaderSetup::MakeShared();
    shapePipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Shaders/ColorMesh.fx", "ColorMeshVS");
    shapePipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Shaders/ColorMesh.fx", "ColorMeshPS");
    shapePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
    shapePipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
    AstrumRenderer::Instance().DefaultShapeShaderPipeline = shapePipeline;
}

void AstrumRenderer::CreateAndSetDefaultMaterialPipeline() {
    auto texturePipeline = AstrumShaderSetup::MakeShared();
    texturePipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Shaders/Mesh.fx", "MeshVS");
    texturePipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Shaders/Mesh.fx", "DefaultMaterialPS");
    texturePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
    texturePipeline->AddInputLayoutDescription("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0);
    AstrumRenderer::Instance().DefaultTextureShaderPipeline = texturePipeline;
}

AstrumResolution AstrumRenderer::GetResolution() const {
    return resolution;
}

AstrumVector2 AstrumRenderer::GetRSRate() const {
    auto clientRect = AstrumWindow::GetClientSize();
    return AstrumVector2{
        static_cast<float>(static_cast<double>(resolution.Width) / static_cast<double>(clientRect.Width)),
        static_cast<float>(static_cast<double>(resolution.Height) / static_cast<double>(clientRect.Height))
     };
}

uint32_t AstrumRenderer::SampleCount() const { return sampleCount; }