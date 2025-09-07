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
#pragma comment(lib, "Astrum/ThirdParty/DirectXTex_Debug.lib")
#else
#pragma comment(lib, "Astrum/ThirdParty/DirectXTex.lib")
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

	operator bool() const { return image != nullptr; }
private:
	std::unique_ptr<DirectX::ScratchImage> image = std::make_unique<DirectX::ScratchImage>();
};