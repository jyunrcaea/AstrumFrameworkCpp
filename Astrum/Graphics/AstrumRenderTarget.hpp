#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>
#include "../Resources/IAstrumTexture.hpp"
#include "../Units/AstrumColor.hpp"

// D3D11 렌더 타깃을 관리하는 클래스
class AstrumRenderTarget : public IAstrumTexture {
public:
    AstrumRenderTarget(unsigned int width, unsigned int height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, unsigned int sampleCount = 32);

    // RenderTarget 바인딩 (이 타깃에 그리기 시작)
    void Bind();
    // 이전 렌더 타깃으로 복원
    void Unbind();
    // 클리어
    void Clear();

    // 결과 이미지를 텍스처로 사용
    virtual ID3D11ShaderResourceView* GetShaderResourceView() const override { return shaderResourceView.Get(); }
    ID3D11RenderTargetView* GetRenderTargetView() const { return renderTargetView.Get(); }
    ID3D11Texture2D* GetTexture() const { return texture.Get(); }
    virtual unsigned int GetWidth() const override { return width; }
    virtual unsigned int GetHeight() const override { return height; }

    AstrumColor BackgroundColor{ 0, 0, 0, 0 };
private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
    unsigned int width = 0, height = 0;

    // 이전 상태 저장용
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> previousRTV;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> previousDSV;

    void ResetViewPort() const;
    void ClearShaderResourceView() const;
public:
    static std::shared_ptr<AstrumRenderTarget> MakeShared(unsigned int width, unsigned int height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, unsigned int sampleCount = 512) {
        return std::make_shared<AstrumRenderTarget>(width, height, format, sampleCount);
	}
};