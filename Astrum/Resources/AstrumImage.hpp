#pragma once
#include <string>
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

class AstrumImage
{
public:
	AstrumImage(const std::filesystem::path& path);
	AstrumImage(std::filesystem::path&& path);
	AstrumImage(AstrumImage&& image) noexcept;
    ~AstrumImage();

	size_t GetWidth() const;
	size_t GetHeight() const;

	const DirectX::Image* GetImages() const;
	const size_t GetImageCount() const;
	const DirectX::TexMetadata& GetMetadata() const;

	bool IsVaild() const noexcept { return image != nullptr && image->GetImageCount() > 0; }
	operator bool() const noexcept { return image != nullptr; }
private:
	std::unique_ptr<DirectX::ScratchImage> image = std::make_unique<DirectX::ScratchImage>();

public:
	static std::shared_ptr<AstrumImage> MakeShared(const std::filesystem::path& path) { return std::make_shared<AstrumImage>(path); }
	static std::shared_ptr<AstrumImage> MakeShared(std::filesystem::path&& path) { return std::make_shared<AstrumImage>(std::move(path)); }
};