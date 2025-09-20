#include "AstrumFonts.hpp"
#include "AstrumTargetFont.hpp"
#include "../AstrumException.hpp"

std::shared_ptr<AstrumTargetFont> AstrumFonts::GetFont(const std::wstring& fontName, float fontSize, int weight) const {
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
	if (FAILED(GetWriteFactory()->CreateTextFormat(
		fontName.c_str(),
		this->fontCollection.Get(),
		static_cast<DWRITE_FONT_WEIGHT>(weight),
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"en-us",
		textFormat.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to create text format for font.").Alert();

	return AstrumTargetFont::MakeShared(GetWriteFactory(), std::move(textFormat), fontSize);
}

const std::wstring& AstrumFonts::GetFaceName() const {
	return faceName;
}

Microsoft::WRL::ComPtr<IDWriteFactory5> AstrumFonts::GetWriteFactory() const {
	static Microsoft::WRL::ComPtr<IDWriteFactory5> factory;
	if (factory) return factory;

	if (FAILED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory5),
		reinterpret_cast<IUnknown**>(factory.GetAddressOf())
	))) AstrumException(__LINE__, __FILE__, "Failed to create DWrite factory.").Alert();

	return factory;
}

void AstrumFonts::Initialize(const std::filesystem::path::value_type* pathstr) {
	Microsoft::WRL::ComPtr<IDWriteFontFile> fontFile = nullptr;
	if (FAILED(GetWriteFactory()->CreateFontFileReference(
		pathstr,
		nullptr,
		fontFile.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to create font file reference.").Alert();

	Microsoft::WRL::ComPtr<IDWriteFontSetBuilder1> fontBuilder = nullptr;
	if (FAILED(GetWriteFactory()->CreateFontSetBuilder(
		fontBuilder.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to create font set builder.").Alert();

	fontBuilder->AddFontFile(fontFile.Get());

	Microsoft::WRL::ComPtr<IDWriteFontSet> fontSet = nullptr;
	if (FAILED(fontBuilder->CreateFontSet(
		fontSet.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to create font set.").Alert();

	if (FAILED(GetWriteFactory()->CreateFontCollectionFromFontSet(
		fontSet.Get(),
		this->fontCollection.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to create font collection from font set.").Alert();

	Microsoft::WRL::ComPtr<IDWriteFontFamily> fontFamily = nullptr;
	if (FAILED(this->fontCollection->GetFontFamily(
		0,
		fontFamily.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to get font family from collection.").Alert();

	Microsoft::WRL::ComPtr<IDWriteLocalizedStrings> localName = nullptr;
	if (FAILED(fontFamily->GetFamilyNames(
		localName.GetAddressOf()
	))) AstrumException(__LINE__, __FILE__, "Failed to get localized font names.").Alert();

	unsigned int nameLength;
	if (FAILED(localName->GetStringLength(
		0,
		&nameLength
	))) AstrumException(__LINE__, __FILE__, "Failed to get localized font name length.").Alert();

	this->faceName.resize(static_cast<size_t>(nameLength) + 1, L'\0');
	if (FAILED(localName->GetString(
		0,
		this->faceName.data(),
		static_cast<unsigned int>(this->faceName.size())
	))) AstrumException(__LINE__, __FILE__, "Failed to get localized font name string.").Alert();
}
