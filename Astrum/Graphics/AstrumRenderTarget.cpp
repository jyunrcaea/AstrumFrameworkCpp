#include "AstrumRenderTarget.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

using Microsoft::WRL::ComPtr;

AstrumRenderTarget::AstrumRenderTarget(unsigned int width, unsigned int height, DXGI_FORMAT format, unsigned int sampleCount)
    : width(width), height(height)
{
    ID3D11Device* const device = AstrumRenderer::Instance().GetDevice();

    if (sampleCount >= 32) sampleCount = AstrumRenderer::Instance().GetSampleCount();

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

    context->OMGetRenderTargets(1, previousRTV.GetAddressOf(), previousDSV.GetAddressOf()); //이전 상태 저장
	ClearShaderResourceView(); // 셰이더 리소스 뷰 초기화
    context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get()); // 현재 렌더 타깃으로 바인딩
    ResetViewPort(); // 뷰 포트 맞춰주기
}

void AstrumRenderTarget::Unbind()
{
    ClearShaderResourceView();
	// 이전 상태로 복원
    AstrumRenderer::Instance().GetContext()->OMSetRenderTargets(1, previousRTV.GetAddressOf(), previousDSV.Get());
    previousRTV = nullptr;
    previousDSV = nullptr;
}

void AstrumRenderTarget::Clear() {
	auto* const context = AstrumRenderer::Instance().GetContext();
    context->ClearRenderTargetView(renderTargetView.Get(), reinterpret_cast<float*>(&BackgroundColor));
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void AstrumRenderTarget::ResetViewPort() const {
    D3D11_VIEWPORT vp{};
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    vp.Width = static_cast<float>(width);
    vp.Height = static_cast<float>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    AstrumRenderer::Instance().GetContext()->RSSetViewports(1, &vp);
}

void AstrumRenderTarget::ClearShaderResourceView() const {
    ID3D11ShaderResourceView* const nullSrv[1] = { nullptr };
    AstrumRenderer::Instance().GetContext()->PSSetShaderResources(0, 1, nullSrv);
}