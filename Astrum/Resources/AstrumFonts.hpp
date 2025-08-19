#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <filesystem>
#include "AstrumTargetFont.hpp"

#pragma comment(lib, "DWrite.lib")
#pragma comment(lib, "D2d1.lib")

class AstrumTargetFont;

class AstrumFonts
{
public:
	AstrumFonts(const std::filesystem::path& fontFilePath);
	std::shared_ptr<AstrumTargetFont> GetFont(const std::wstring& fontName, int weight = DWRITE_FONT_WEIGHT_NORMAL, float fontSize = 12.0f) const;

	const std::wstring& GetFaceName() const;
private:
	std::wstring faceName;
	Microsoft::WRL::ComPtr<IDWriteFactory5> GetWriteFactory() const;
	Microsoft::WRL::ComPtr<IDWriteFontCollection1> fontCollection;
};