#include "AstrumRenderTarget.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

using Microsoft::WRL::ComPtr;

AstrumRenderTarget::AstrumRenderTarget(unsigned int width, unsigned int height, DXGI_FORMAT format, unsigned int sampleCount)
    : width(width), height(height)
{
    ID3D11Device* const device = AstrumRenderer::Instance().GetDevice();

    if (sampleCount >= 256) sampleCount = AstrumRenderer::Instance().GetSampleCount();

#pragma region DepthStencilView 생성
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
        throw AstrumException("Failed to create depth buffer.");
    }
    if (FAILED(device->CreateDepthStencilView(depthBuffer.Get(), nullptr, &depthStencilView))) {
        throw AstrumException("Failed to create depth stencil view.");
    }
#pragma endregion

#pragma region RenderTargetTexture 생성
    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = format;
    textureDesc.SampleDesc.Count = sampleCount;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    if (FAILED(device->CreateTexture2D(&textureDesc, nullptr, &texture)))
        throw AstrumException("Failed to create render target texture");
#pragma endregion

    if (FAILED(device->CreateRenderTargetView(texture.Get(), nullptr, &renderTargetView)))
        throw AstrumException("Failed to create render target view");
    if (FAILED(device->CreateShaderResourceView(texture.Get(), nullptr, &shaderResourceView)))
        throw AstrumException("Failed to create shader resource view");
}

void AstrumRenderTarget::Bind()
{
	ID3D11DeviceContext* const context = AstrumRenderer::Instance().GetContext();
    // 이전 상태 저장
    context->OMGetRenderTargets(1, previousRTV.GetAddressOf(), previousDSV.GetAddressOf());
	// 현재 렌더 타깃으로 바인딩
    context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
}

void AstrumRenderTarget::Unbind()
{
	// 이전 상태로 복원
    AstrumRenderer::Instance().GetContext()->OMSetRenderTargets(1, previousRTV.GetAddressOf(), previousDSV.Get());
    previousRTV = nullptr;
    previousDSV = nullptr;
}