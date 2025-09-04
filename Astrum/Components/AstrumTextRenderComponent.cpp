#include "AstrumTextRenderComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Singletons/AstrumWindow.hpp"
#include "../AstrumException.hpp"
#include <cfloat>

using Microsoft::WRL::ComPtr;

AstrumTextRenderComponent::AstrumTextRenderComponent() {
	AstrumRenderer::Instance().GetRenderTarget2D()->CreateSolidColorBrush(
		//{ textColor.Red, textColor.Green, textColor.Blue, textColor.Alpha },
		*reinterpret_cast<D2D1_COLOR_F*>(&textColor),
		colorBrush.GetAddressOf()
	);
}

void AstrumTextRenderComponent::Draw() {
	if (nullptr != GetOwner() && GetOwner()->IsVisible()) {
		AstrumRenderQueue::Enqueue(IAstrumRenderable::shared_from_this());
	}
}

void AstrumTextRenderComponent::PreRender() {
	if (nullptr == targetFont) return;

	 if (colorDirty) {
		colorBrush->SetColor(reinterpret_cast<const D2D1_COLOR_F*>(&textColor));
		colorDirty = false;
	}

	if (layoutDirty || nullptr == textLayout) {
		const auto& [scaleX, scaleY, _] = GetOwner()->GetAbsoluteScale();
		textLayout = targetFont->CreateTextLayout(text, scaleX * layoutWidth, scaleY * layoutHeight);
		if (nullptr != textLayout) {
			textLayout->SetTextAlignment(textAlign);
			textLayout->SetParagraphAlignment(paragraphAlign);
			textLayout->SetWordWrapping(wordWrapping);
		}
		layoutDirty = false;
	}
}

void AstrumTextRenderComponent::Render() {
	if (nullptr == targetFont) return;

	auto* const rt2d = AstrumRenderer::Instance().GetRenderTarget2D();
	if (nullptr == rt2d || nullptr == textLayout) return;

	const auto resolution = AstrumRenderer::Instance().GetResolution();
	const auto& absolutePos = GetOwner()->GetAbsolutePosition();
	D2D1_POINT_2F renderPoint(absolutePos.X + resolution.Width * 0.5f, resolution.Height * 0.5f - absolutePos.Y);
	renderPoint.x -= layoutWidth * 0.5f;
	renderPoint.y -= layoutHeight * 0.5f;

	rt2d->DrawTextLayout(renderPoint, textLayout.Get(), colorBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

void AstrumTextRenderComponent::SetAlignment(AstrumTextHorizontalAlignmentType horizontal, AstrumTextVerticalAlignmentType vertical) {
	textAlign = static_cast<DWRITE_TEXT_ALIGNMENT>(horizontal);
	paragraphAlign = static_cast<DWRITE_PARAGRAPH_ALIGNMENT>(vertical);
	layoutDirty = true;
}
void AstrumTextRenderComponent::SetWordWrapping(DWRITE_WORD_WRAPPING wrap) {
	wordWrapping = wrap;
	layoutDirty = true;
}
void AstrumTextRenderComponent::SetLayoutSize(float width, float height) {
	layoutWidth = width;
	layoutHeight = height;
	layoutDirty = true;
}
