#include "AstrumRenderer.hpp"

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
            DXGI_FORMAT_R8G8B8A8_UNORM, p, &quality)) && quality > 0)
        {
            sampleCount = p;
            break;
        }
    }

    DXGI_SWAP_CHAIN_DESC desc = {};
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.SampleDesc.Count = sampleCount;
    desc.SampleDesc.Quality = 0;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 1;
    desc.OutputWindow = AstrumWindow::Instance().GetHandle();
    desc.Windowed = windowMode;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    ComPtr<IDXGIDevice>   dxgiDevice;
    ComPtr<IDXGIAdapter>  adapter;
    ComPtr<IDXGIFactory>  factory;
    device.As(&dxgiDevice);
    dxgiDevice->GetAdapter(&adapter);
    adapter->GetParent(IID_PPV_ARGS(&factory));

    if (FAILED(factory->CreateSwapChain(device.Get(), &desc, &swapChain))) {
        throw AstrumException("Swap chain creating failed.");
    }

    ComPtr<ID3D11Texture2D> backBuffer;
    if (FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)))) {
        throw AstrumException("Get buffer from swap chain failed.");
    }

    if (FAILED(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &rtv))) {
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
    if (FAILED(device->CreateDepthStencilView(depthBuffer.Get(), nullptr, &dsv))) {
        throw AstrumException("Create depth stencil view failed.");
    }

    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);
}

void AstrumRenderer::Rendering() {
    const auto& c = AstrumWindow::Instance().BackgroundColor;
    float bg[4] = { c.Red, c.Green, c.Blue, c.Alpha };

    context->ClearRenderTargetView(rtv.Get(), bg);
    context->ClearDepthStencilView(dsv.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    context->OMSetRenderTargets(1, rtv.GetAddressOf(), dsv.Get());

    while (!renderQueue.empty()) {
        if (shaderPipeline) shaderPipeline->SetShader();
		auto renderable = renderQueue.front();
        renderable->Rendering();
        renderQueue.pop();
    }

    swapChain->Present(0, 0);
}

void AstrumRenderer::EnqueueRenderable(std::shared_ptr<IAstrumRenderable> renderable) {
    renderQueue.push(std::move(renderable));
}

void AstrumRenderer::Dispose() {
	// do not release these resources here, they are managed by ComPtr
	// and this class is a singleton.
    //if (dsv != nullptr) {
    //    dsv->Release();
    //}
    //if (rtv != nullptr) {
    //    rtv->Release();
    //}
    //if (swapChain != nullptr) {
    //    swapChain->Release();
    //}
    //if (context != nullptr) {
    //    context->Release();
    //}
    //if (device != nullptr) {
    //    device->Release();
    //}
}

ID3D11Device* AstrumRenderer::GetDevice() const {
    return device.Get();
}
ID3D11DeviceContext* AstrumRenderer::GetContext() const {
    return context.Get();
}
uint32_t AstrumRenderer::SampleCount() const {
    return sampleCount;
}