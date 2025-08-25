#pragma once
#include <string>
#include <wrl/client.h>
#include <d2d1.h>
#include <dwrite_3.h>
#include "AstrumComponent.hpp"
#include "../Resources/AstrumTargetFont.hpp"
#include "../Graphics/IAstrumRenderable.hpp"
#include "../Units/AstrumColor.hpp"

class AstrumTextRenderComponent : public AstrumComponent, public IAstrumRenderable
{
public:
	// Lifecycle
	virtual void Prepare() override;
	virtual void Draw() override;

protected:
	virtual void PreRender() override;
	virtual void Render() override;

public:
	// Properties
	void SetText(const std::wstring& t);
	void SetFont(const std::shared_ptr<AstrumTargetFont>& font);
	void SetColor(const AstrumColor& c);
	void SetAlignment(DWRITE_TEXT_ALIGNMENT horizontal, DWRITE_PARAGRAPH_ALIGNMENT vertical);
	void SetWordWrapping(DWRITE_WORD_WRAPPING wrap);
	// 0 for width/height means unlimited (no wrapping) for that axis.
	void SetLayoutSize(float width, float height);
	// Pivot in [0..1] range (0,0)=top-left, (0.5,0.5)=center, (1,1)=bottom-right)
	void SetPivot(float x, float y);

	const std::wstring& GetText() const { return text; }
	std::shared_ptr<AstrumTargetFont> GetFont() const { return targetFont; }
	AstrumColor GetColor() const { return textColor; }

private:
	std::shared_ptr<AstrumTargetFont> targetFont = nullptr;
	std::wstring text;
	AstrumColor textColor = AstrumColor::White;
	float layoutWidth = 0.f;
	float layoutHeight = 0.f;
	float pivotX = 0.0f; // top-left by default
	float pivotY = 0.0f;
	DWRITE_TEXT_ALIGNMENT textAlign = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlign = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	DWRITE_WORD_WRAPPING wordWrapping = DWRITE_WORD_WRAPPING_WRAP;

	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush = nullptr;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
	bool layoutDirty = true;
	bool colorDirty = true;
};
