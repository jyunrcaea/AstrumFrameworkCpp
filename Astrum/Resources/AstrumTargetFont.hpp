#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <filesystem>
#include "AstrumFonts.hpp"

namespace Astrum
{
	class Fonts;

	class TargetFont
	{
		friend class Fonts;

	public:
		TargetFont(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat)
			: writeFactory(factory), textFormat(textFormat) {}

	private:
		const Microsoft::WRL::ComPtr<IDWriteFactory5> writeFactory;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;

	public:
		static std::shared_ptr<TargetFont> MakeShared(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat) {
			return std::make_shared<TargetFont>(factory, std::move(textFormat));
		}
	};
}