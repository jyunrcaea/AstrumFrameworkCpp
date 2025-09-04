#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <memory>

class AstrumFonts;

// DirectWrite text format wrapper for Astrum.
class AstrumTargetFont
{
	friend class AstrumFonts;

public:
	AstrumTargetFont(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat, float fontSize)
		: writeFactory(factory), textFormat(textFormat), fontSize(fontSize) {}

	// Access to the underlying text format.
	IDWriteTextFormat* GetTextFormat() const { return textFormat.Get(); }
	// Create a layout for the given text and layout bounds (0 means auto/no limit).
	Microsoft::WRL::ComPtr<IDWriteTextLayout> CreateTextLayout(const std::wstring& text, float layoutWidth, float layoutHeight) const;

	float GetFontSize() const { return fontSize;  }
	void SetFontSize(float newFontSize) { fontSize = newFontSize; }
private:
	const Microsoft::WRL::ComPtr<IDWriteFactory5> writeFactory;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;
	float fontSize = 12.f;

public:
	static std::shared_ptr<AstrumTargetFont> MakeShared(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat, float fontSize) {
		return std::make_shared<AstrumTargetFont>(factory, std::move(textFormat), fontSize);
	}
};