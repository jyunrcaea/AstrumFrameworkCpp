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

protected:
	AstrumTargetFont(const Microsoft::WRL::ComPtr<IDWriteTextFormat>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat)
		: writeFactory(factory), textFormat(textFormat) { }

private:
	const Microsoft::WRL::ComPtr<IDWriteTextFormat> writeFactory;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;
}