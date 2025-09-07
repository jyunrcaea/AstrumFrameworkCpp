#pragma once
#include <string>
#include <wrl/client.h>
#include <d2d1.h>
#include <dwrite_3.h>
#include "AstrumComponent.hpp"
#include "../Resources/AstrumTargetFont.hpp"
#include "../Graphics/IAstrumRenderable.hpp"
#include "../Units/AstrumColor.hpp"
#include "../Enums/AstrumTextAlignmentType.hpp"

class AstrumTextRenderComponent : public AstrumComponent, public IAstrumRenderable
{
public:
	AstrumTextRenderComponent();
	virtual void Draw() override;

protected:
	virtual void PreRender() override;
	virtual void Render() override;

public:
	template <typename T>
	requires std::same_as<std::remove_cvref_t<T>, std::wstring>
	void SetText(T&& newText);
	template <typename T>
	requires std::same_as<std::remove_cvref_t<T>, std::shared_ptr<AstrumTargetFont>>
	void SetFont(T&& newFont);
	template <typename T>
	requires std::same_as<std::remove_cvref_t<T>, AstrumColor>
	void SetColor(T&& newTextColor);
	void SetAlignment(AstrumTextHorizontalAlignmentType horizontal, AstrumTextVerticalAlignmentType vertical);
	void SetWordWrapping(DWRITE_WORD_WRAPPING wrap);
	// 0 for width/height means unlimited (no wrapping) for that axis.
	void SetLayoutSize(float width, float height);

	const std::wstring& GetText() const { return text; }
	std::shared_ptr<AstrumTargetFont> GetFont() const { return targetFont; }
	AstrumColor GetColor() const { return textColor; }

	float GetWidth() const { return layoutWidth; }
	float GetHeight() const { return layoutHeight; }
	void SetWidth(float newWidth) { layoutWidth = newWidth; }
	void SetHeight(float newHeight) { layoutHeight = newHeight; }
private:
	std::shared_ptr<AstrumTargetFont> targetFont = nullptr;
	std::wstring text;
	AstrumColor textColor = AstrumColor::Black;
	float layoutWidth = 400.f;
	float layoutHeight = 100.f;
	DWRITE_TEXT_ALIGNMENT textAlign = DWRITE_TEXT_ALIGNMENT_CENTER;
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlign = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	DWRITE_WORD_WRAPPING wordWrapping = DWRITE_WORD_WRAPPING_WRAP;

	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush = nullptr;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
	bool layoutDirty = true;
	bool colorDirty = true;
};

template<typename T>
requires std::same_as<std::remove_cvref_t<T>, std::wstring>
inline void AstrumTextRenderComponent::SetText(T&& newText) {
	text = std::forward<T>(newText);
	layoutDirty = true;
}

template<typename T>
requires std::same_as<std::remove_cvref_t<T>, std::shared_ptr<AstrumTargetFont>>
inline void AstrumTextRenderComponent::SetFont(T&& newFont) {
	targetFont = std::forward<T>(newFont);
	layoutDirty = true;
}

template<typename T>
requires std::same_as<std::remove_cvref_t<T>, AstrumColor>
inline void AstrumTextRenderComponent::SetColor(T&& newTextColor) {
	textColor = std::forward<T>(newTextColor);
	colorDirty = true;
}