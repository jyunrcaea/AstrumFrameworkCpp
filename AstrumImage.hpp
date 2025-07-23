#pragma once
#include <string>
#include <filesystem>
#include <wincodec.h>
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "DirectXTex.h"
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

#ifdef _DEBUG
#pragma comment(lib, "ThirdParty/DirectXTex_Debug.lib")
#else
#pragma comment(lib, "ThirdParty/DirectXTex.lib")
#endif

class AstrumImage
{
public:
	AstrumImage(const std::filesystem::path& path);
    ~AstrumImage();

	size_t GetWidth() const;
	size_t GetHeight() const;

	const DirectX::Image* GetImages() const;
	const size_t GetImageCount() const;
	const DirectX::TexMetadata& GetMetadata() const;
private:
	DirectX::ScratchImage* image;
};