#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <wincodec.h>
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "../DirectXTex.h"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

/// <summary>
/// 이미지 파일을 로드하고 관리하는 클래스입니다. DirectXTex 라이브러리를 사용합니다.
/// </summary>
class AstrumImage
{
public:
	/// <summary>
	/// 이미지 파일을 로드합니다. (절대 경로 또는 상대 경로)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	AstrumImage(const std::filesystem::path& path);
	/// <summary>
	/// 이미지 파일을 로드합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	AstrumImage(std::filesystem::path&& path);
	/// <summary>
	/// 이미지를 이동 생성자로 생성합니다.
	/// </summary>
	/// <param name="image">이동할 이미지입니다.</param>
	AstrumImage(AstrumImage&& image) noexcept;
	/// <summary>
	/// 이미지를 소멸합니다.
	/// </summary>
    ~AstrumImage();

	/// <summary>
	/// 이미지의 너비를 반환합니다.
	/// </summary>
	/// <returns>이미지의 너비(픽셀)입니다.</returns>
	size_t GetWidth() const;
	/// <summary>
	/// 이미지의 높이를 반환합니다.
	/// </summary>
	/// <returns>이미지의 높이(픽셀)입니다.</returns>
	size_t GetHeight() const;

	/// <summary>
	/// 이미지 데이터 배열을 반환합니다.
	/// </summary>
	/// <returns>이미지 배열 포인터입니다.</returns>
	const DirectX::Image* GetImages() const;
	/// <summary>
	/// 이미지 개수를 반환합니다.
	/// </summary>
	/// <returns>로드된 이미지 개수입니다.</returns>
	const size_t GetImageCount() const;
	/// <summary>
	/// 이미지의 메타데이터를 반환합니다.
	/// </summary>
	/// <returns>이미지 메타데이터 참조입니다.</returns>
	const DirectX::TexMetadata& GetMetadata() const;

	/// <summary>
	/// 이미지가 유효한지 확인합니다.
	/// </summary>
	/// <returns>이미지가 유효하면 true, 아니면 false를 반환합니다.</returns>
	bool IsVaild() const noexcept { return image != nullptr && image->GetImageCount() > 0; }
	/// <summary>
	/// 이미지가 유효한지 확인합니다. (bool 변환 연산자)
	/// </summary>
	operator bool() const noexcept { return image != nullptr; }
private:
	/// <summary>
	/// DirectXTex 스크래치 이미지입니다.
	/// </summary>
	std::unique_ptr<DirectX::ScratchImage> image = std::make_unique<DirectX::ScratchImage>();

public:
	/// <summary>
	/// AstrumImage 객체의 공유 포인터를 생성합니다. (절대 경로 또는 상대 경로)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumImage 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumImage> MakeShared(const std::filesystem::path& path) { return std::make_shared<AstrumImage>(path); }
	/// <summary>
	/// AstrumImage 객체의 공유 포인터를 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumImage 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumImage> MakeShared(std::filesystem::path&& path) { return std::make_shared<AstrumImage>(std::move(path)); }
};