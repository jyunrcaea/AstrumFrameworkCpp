#include "AstrumFonts.hpp"
#include "../AstrumException.hpp"

AstrumFonts::AstrumFonts(const std::filesystem::path& fontFilePath) {
	Microsoft::WRL::ComPtr<IDWriteFontFile> fontFile = nullptr;
	if (FAILED(GetWriteFactory()->CreateFontFileReference(
		fontFilePath.c_str(),
		nullptr,
		fontFile.GetAddressOf()
	))) throw AstrumException("Failed to create font file reference.");

	Microsoft::WRL::ComPtr<IDWriteFontSetBuilder1> fontBuilder = nullptr;
	if (FAILED(GetWriteFactory()->CreateFontSetBuilder(
		fontBuilder.GetAddressOf()
	))) throw AstrumException("Failed to create font set builder.");

	fontBuilder->AddFontFile(fontFile.Get());

	Microsoft::WRL::ComPtr<IDWriteFontSet> fontSet = nullptr;
	if (FAILED(fontBuilder->CreateFontSet(
		fontSet.GetAddressOf()
	))) throw AstrumException("Failed to create font set.");

	if (FAILED(GetWriteFactory()->CreateFontCollectionFromFontSet(
		fontSet.Get(),
		this->fontCollection.GetAddressOf()
	))) throw AstrumException("Failed to create font collection from font set.");

	Microsoft::WRL::ComPtr<IDWriteFontFamily> fontFamily = nullptr;
	if (FAILED(this->fontCollection->GetFontFamily(
		0,
		fontFamily.GetAddressOf()
	))) throw AstrumException("Failed to get font family from collection.");

	Microsoft::WRL::ComPtr<IDWriteLocalizedStrings> localName = nullptr;
	if (FAILED(fontFamily->GetFamilyNames(
		localName.GetAddressOf()
	))) throw AstrumException("Failed to get localized font names.");

	unsigned int nameLength;
	if (FAILED(localName->GetStringLength(
		0,
		&nameLength
	))) throw AstrumException("Failed to get localized font name length.");

	this->faceName.resize(static_cast<size_t>(nameLength) + 1, L'\0');
	if (FAILED(localName->GetString(
		0,
		this->faceName.data(),
		static_cast<unsigned int>(this->faceName.size())
	))) throw AstrumException("Failed to get localized font name string.");
}

std::shared_ptr<AstrumTargetFont> AstrumFonts::GetFont(const std::wstring& fontName, int weight, float fontSize) const {
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
	if (FAILED(GetWriteFactory()->CreateTextFormat(
		fontName.c_str(),
		this->fontCollection.Get(),
		static_cast<DWRITE_FONT_WEIGHT>(weight),
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		this->faceName.c_str(),
		textFormat.GetAddressOf()
	))) throw AstrumException("Failed to create text format for font.");

	return AstrumTargetFont::MakeShared(GetWriteFactory(), std::move(textFormat));
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
	))) throw AstrumException("Failed to create DWrite factory.");

	return factory;
}