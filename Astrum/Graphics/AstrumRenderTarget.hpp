#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>
#include "../Resources/IAstrumTexture.hpp"
#include "../Units/AstrumColor.hpp"

// D3D11 렌더 타깃을 관리하는 클래스
class AstrumRenderTarget : public IAstrumTexture {
public:
    /// <summary>
    /// 렌더 타깃을 생성합니다.
    /// </summary>
    /// <param name="width">렌더 타깃의 너비(픽셀)입니다.</param>
    /// <param name="height">렌더 타깃의 높이(픽셀)입니다.</param>
    /// <param name="format">렌더 타깃의 픽셀 형식입니다. 기본값은 DXGI_FORMAT_R8G8B8A8_UNORM입니다.</param>
    /// <param name="sampleCount">다중 샘플링 개수입니다. 기본값은 1입니다.</param>
    AstrumRenderTarget(unsigned int width, unsigned int height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, unsigned int sampleCount = 1);

    /// <summary>
    /// 이 렌더 타깃을 렌더링 파이프라인에 바인딩하여 그리기를 시작합니다.
    /// </summary>
    void Bind();
    /// <summary>
    /// 이전 렌더 타깃으로 복원합니다.
    /// </summary>
    void Unbind();
    /// <summary>
    /// 렌더 타깃을 배경색으로 초기화합니다.
    /// </summary>
    void Clear();

    /// <summary>
    /// 셰이더에서 사용할 수 있는 셰이더 리소스 뷰를 반환합니다.
    /// </summary>
    /// <returns>셰이더 리소스 뷰 포인터입니다.</returns>
    virtual ID3D11ShaderResourceView* GetShaderResourceView() const override { return shaderResourceView.Get(); }
    /// <summary>
    /// 렌더 타깃 뷰 포인터를 반환합니다.
    /// </summary>
    /// <returns>렌더 타깃 뷰 포인터입니다.</returns>
    ID3D11RenderTargetView* GetRenderTargetView() const { return renderTargetView.Get(); }
    /// <summary>
    /// Direct3D 텍스처 포인터를 반환합니다.
    /// </summary>
    /// <returns>2D 텍스처 포인터입니다.</returns>
    ID3D11Texture2D* GetTexture() const { return texture.Get(); }
    /// <summary>
    /// 렌더 타깃의 너비를 반환합니다.
    /// </summary>
    /// <returns>렌더 타깃의 너비(픽셀)입니다.</returns>
    virtual unsigned int GetWidth() const override { return width; }
    /// <summary>
    /// 렌더 타깃의 높이를 반환합니다.
    /// </summary>
    /// <returns>렌더 타깃의 높이(픽셀)입니다.</returns>
    virtual unsigned int GetHeight() const override { return height; }

    /// <summary>
    /// 렌더 타깃을 초기화할 때 사용할 배경색입니다. 기본값은 검은색(0, 0, 0, 0)입니다.
    /// </summary>
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
    /// <summary>
    /// AstrumRenderTarget 객체의 공유 포인터를 생성합니다.
    /// </summary>
    /// <param name="width">렌더 타깃의 너비(픽셀)입니다.</param>
    /// <param name="height">렌더 타깃의 높이(픽셀)입니다.</param>
    /// <param name="format">렌더 타깃의 픽셀 형식입니다. 기본값은 DXGI_FORMAT_R8G8B8A8_UNORM입니다.</param>
    /// <param name="sampleCount">다중 샘플링 개수입니다. 기본값은 1입니다.</param>
    /// <returns>새로 생성된 AstrumRenderTarget 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumRenderTarget> MakeShared(unsigned int width, unsigned int height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, unsigned int sampleCount = 1) {
        return std::make_shared<AstrumRenderTarget>(width, height, format, sampleCount);
	}
};