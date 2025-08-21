#include "AstrumRenderTarget.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

using Microsoft::WRL::ComPtr;

AstrumRenderTarget::AstrumRenderTarget(unsigned int width, unsigned int height, DXGI_FORMAT format, unsigned int sampleCount)
    : width(width), height(height)
{
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = format;
    texDesc.SampleDesc.Count = sampleCount;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;

    ID3D11Device* const device = AstrumRenderer::Instance().GetDevice();
    if (FAILED(device->CreateTexture2D(&texDesc, nullptr, &texture)))
        throw AstrumException("Failed to create render target texture");
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
    context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), AstrumRenderer::Instance().GetDepthStencilView());
}

void AstrumRenderTarget::Unbind()
{
    AstrumRenderer::Instance().GetContext()->OMSetRenderTargets(1, previousRTV.GetAddressOf(), previousDSV.Get());
    previousRTV = nullptr;
    previousDSV = nullptr;
}