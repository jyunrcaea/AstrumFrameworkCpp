#include "AstrumTargetFont.hpp"
#include "../AstrumException.hpp"

using Microsoft::WRL::ComPtr;

ComPtr<IDWriteTextLayout> AstrumTargetFont::CreateTextLayout(const std::wstring& text, float layoutWidth, float layoutHeight) const
{
    ComPtr<IDWriteTextLayout> layout;
    if (nullptr == writeFactory || nullptr == textFormat) return layout;

    if (FAILED(writeFactory->CreateTextLayout(
        text.c_str(),
        static_cast<UINT32>(text.length()),
        textFormat.Get(),
        layoutWidth,
        layoutHeight,
        layout.GetAddressOf()
    ))) return nullptr;

    layout->SetFontSize(fontSize, DWRITE_TEXT_RANGE{ 0, static_cast<unsigned int>(text.length()) });

    return layout;
}