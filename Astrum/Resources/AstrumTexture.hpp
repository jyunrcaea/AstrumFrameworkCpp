#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>
#include <string>
#include <memory>
#include <filesystem>
#include "AstrumImage.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "IAstrumTexture.hpp"

/// <summary>
/// Direct3D 텍스처를 관리하는 클래스입니다. 이미지 파일을 로드하여 GPU 리소스로 변환합니다.
/// </summary>
class AstrumTexture : public IAstrumTexture
{
private:
    /// <summary>
    /// 복사 생성자를 삭제합니다. (복사 불가)
    /// </summary>
    AstrumTexture(const AstrumTexture&) = delete;
    /// <summary>
    /// 복사 할당 연산자를 삭제합니다. (복사 불가)
    /// </summary>
    AstrumTexture& operator=(const AstrumTexture&) = delete;

public:
    /// <summary>
    /// 이미지 파일을 로드하여 텍스처를 생성합니다. (절대 경로 또는 상대 경로)
    /// </summary>
    /// <param name="path">로드할 이미지 파일의 경로입니다.</param>
    AstrumTexture(const std::filesystem::path& path);
    /// <summary>
    /// 이미지 파일을 로드하여 텍스처를 생성합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="path">로드할 이미지 파일의 경로입니다.</param>
    AstrumTexture(std::filesystem::path&& path);
    /// <summary>
    /// AstrumImage 객체로부터 텍스처를 생성합니다.
    /// </summary>
    /// <param name="image">로드된 이미지 객체입니다.</param>
    AstrumTexture(const std::shared_ptr<AstrumImage>& image);
    /// <summary>
    /// AstrumImage 객체로부터 텍스처를 생성합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="image">로드된 이미지 객체입니다.</param>
    AstrumTexture(std::shared_ptr<AstrumImage>&& image);

    /// <summary>
    /// 셰이더에서 사용할 수 있는 셰이더 리소스 뷰를 반환합니다.
    /// </summary>
    /// <returns>셰이더 리소스 뷰 포인터입니다.</returns>
    virtual ID3D11ShaderResourceView* GetShaderResourceView() const override;
    /// <summary>
    /// 텍스처의 너비를 반환합니다.
    /// </summary>
    /// <returns>텍스처의 너비(픽셀)입니다.</returns>
    virtual unsigned int GetWidth() const override;
    /// <summary>
    /// 텍스처의 높이를 반환합니다.
    /// </summary>
    /// <returns>텍스처의 높이(픽셀)입니다.</returns>
    virtual unsigned int GetHeight() const override;

	/// <summary>
	/// 텍스처가 유효한지 확인합니다.
	/// </summary>
	/// <returns>텍스처가 유효하면 true, 아니면 false를 반환합니다.</returns>
	bool IsValid() const noexcept { return shaderResourceView != nullptr; }
	/// <summary>
	/// 텍스처가 유효한지 확인합니다. (bool 변환 연산자)
	/// </summary>
	operator bool() const noexcept { return shaderResourceView != nullptr; }
private:
	/// <summary>
	/// Direct3D 셰이더 리소스 뷰입니다.
	/// </summary>
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	/// <summary>
	/// 텍스처의 너비(픽셀)입니다.
	/// </summary>
    unsigned int width = 0, height = 0;
	/// <summary>
	/// 원본 이미지 객체입니다. (GPU가 텍스쳐를 로드하는 동안 원본 이미지가 유효해야하니까.)
	/// </summary>
    std::shared_ptr<AstrumImage> sourceImage = nullptr;

public:
	/// <summary>
	/// AstrumTexture 객체의 공유 포인터를 생성합니다. (절대 경로 또는 상대 경로)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumTexture 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumTexture> MakeShared(const std::filesystem::path& path) { return std::make_shared<AstrumTexture>(path); }
	/// <summary>
	/// AstrumTexture 객체의 공유 포인터를 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumTexture 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumTexture> MakeShared(std::filesystem::path&& path) { return std::make_shared<AstrumTexture>(std::move(path)); }
	/// <summary>
	/// AstrumTexture 객체의 공유 포인터를 생성합니다. (이미지 객체로부터)
	/// </summary>
	/// <param name="image">로드된 이미지 객체입니다.</param>
	/// <returns>새로 생성된 AstrumTexture 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumTexture> MakeShared(const std::shared_ptr<AstrumImage>& image) { return std::make_shared<AstrumTexture>(image); }
};