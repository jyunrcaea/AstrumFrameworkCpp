#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <filesystem>
#include "AstrumFonts.hpp"

class AstrumTargetFont
{
	friend class AstrumFonts;

public:
	AstrumTargetFont(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat)
		: writeFactory(factory), textFormat(textFormat) {}

private:
	const Microsoft::WRL::ComPtr<IDWriteFactory5> writeFactory;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;

public:
	static std::shared_ptr<AstrumTargetFont> MakeShared(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat) {
		return std::make_shared<AstrumTargetFont>(factory, std::move(textFormat));
	}
};