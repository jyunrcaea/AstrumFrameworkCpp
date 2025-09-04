#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <filesystem>
#include <memory>

#pragma comment(lib, "DWrite.lib")
#pragma comment(lib, "D2d1.lib")

class AstrumTargetFont;

// 글꼴 컬렉션
class AstrumFonts
{
	friend class AstrumTargetFont;
public:
	AstrumFonts(const std::filesystem::path& fontFilePath) { Initialize(fontFilePath.c_str()); }
	AstrumFonts(std::filesystem::path&& fontFilePath) { Initialize(fontFilePath.c_str()); }
	std::shared_ptr<AstrumTargetFont> GetFont(const std::wstring& fontName, float fontSize = 24.0f, int weight = DWRITE_FONT_WEIGHT_NORMAL) const;

	const std::wstring& GetFaceName() const;
private:
	std::wstring faceName;
	Microsoft::WRL::ComPtr<IDWriteFactory5> GetWriteFactory() const;
	Microsoft::WRL::ComPtr<IDWriteFontCollection1> fontCollection;

	void Initialize(const std::filesystem::path::value_type* pathstr);

public:
	static std::shared_ptr<AstrumFonts> MakeShared(const std::filesystem::path& fontFilePath) { return std::make_shared<AstrumFonts>(fontFilePath); }
	static std::shared_ptr<AstrumFonts> MakeShared(std::filesystem::path&& fontFilePath) { return std::make_shared<AstrumFonts>(std::move(fontFilePath)); }
};
