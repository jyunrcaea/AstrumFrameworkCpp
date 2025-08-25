#include "AstrumTextRenderComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Singletons/AstrumWindow.hpp"
#include "../AstrumException.hpp"
#include <cfloat>

using Microsoft::WRL::ComPtr;

static inline D2D1_MATRIX_3X2_F Multiply(const D2D1_MATRIX_3X2_F& a, const D2D1_MATRIX_3X2_F& b) {
	D2D1_MATRIX_3X2_F r;
	r._11 = a._11 * b._11 + a._12 * b._21;
	r._12 = a._11 * b._12 + a._12 * b._22;
	r._21 = a._21 * b._11 + a._22 * b._21;
	r._22 = a._21 * b._12 + a._22 * b._22;
	r._31 = a._31 * b._11 + a._32 * b._21 + b._31;
	r._32 = a._31 * b._12 + a._32 * b._22 + b._32;
	return r;
}

void AstrumTextRenderComponent::Prepare() {
	auto* rt2d = AstrumRenderer::Instance().GetRenderTarget2D();
	if (nullptr == rt2d) throw AstrumException("D2D RenderTarget is not initialized.");
	if (!brush) {
		D2D1_COLOR_F c{ textColor.Red, textColor.Green, textColor.Blue, textColor.Alpha };
		rt2d->CreateSolidColorBrush(c, brush.GetAddressOf());
		colorDirty = false;
	}
}

void AstrumTextRenderComponent::Draw() {
	if (nullptr != GetOwner() && GetOwner()->IsVisible()) {
		AstrumRenderQueue::Enqueue(IAstrumRenderable::shared_from_this());
	}
}

void AstrumTextRenderComponent::PreRender() {
	// No heavy work here; layout is prepared in Render() when needed.
}

void AstrumTextRenderComponent::Render() {
	if (nullptr == GetOwner() || nullptr == targetFont) return;

	auto* rt2d = AstrumRenderer::Instance().GetRenderTarget2D();
	if (nullptr == rt2d) return;

	if (!brush) {
		D2D1_COLOR_F c{ textColor.Red, textColor.Green, textColor.Blue, textColor.Alpha };
		rt2d->CreateSolidColorBrush(c, brush.GetAddressOf());
		colorDirty = false;
	}
	else if (colorDirty) {
		brush->SetColor(D2D1::ColorF(textColor.Red, textColor.Green, textColor.Blue, textColor.Alpha));
		colorDirty = false;
	}

	// Rebuild layout if needed
	if (layoutDirty || !textLayout) {
		// Fallback to window size instead of FLT_MAX to satisfy DirectWrite layout bounds limits.
		const float fallbackW = static_cast<float>(AstrumWindow::GetWidth());
		const float fallbackH = static_cast<float>(AstrumWindow::GetHeight());
		float w = (layoutWidth <= 0.f) ? (fallbackW > 0.f ? fallbackW : 1024.f) : layoutWidth;
		float h = (layoutHeight <= 0.f) ? (fallbackH > 0.f ? fallbackH : 1024.f) : layoutHeight;
		textLayout = targetFont->CreateTextLayout(text, w, h);
		if (textLayout) {
			textLayout->SetTextAlignment(textAlign);
			textLayout->SetParagraphAlignment(paragraphAlign);
			textLayout->SetWordWrapping(wordWrapping);
		}
		layoutDirty = false;
	}

	if (!textLayout) return;

	// Compute pivot offset from layout metrics
	DWRITE_TEXT_METRICS metrics{};
	textLayout->GetMetrics(&metrics);
	const float anchorX = metrics.widthIncludingTrailingWhitespace * pivotX;
	const float anchorY = metrics.height * pivotY;

	// Build world transform for D2D (center-origin + Y-up mapping)
	const float W = static_cast<float>(AstrumWindow::GetWidth());
	const float H = static_cast<float>(AstrumWindow::GetHeight());
	const auto& pos = GetOwner()->GetAbsolutePosition();
	const auto& rot = GetOwner()->GetAbsoluteRotation();
	const auto& scl = GetOwner()->GetAbsoluteScale();

	auto Tcenter = D2D1::Matrix3x2F::Translation(W * 0.5f, H * 0.5f);
	auto SflipY  = D2D1::Matrix3x2F::Scale(D2D1::SizeF(1.f, -1.f));
	auto Tpos    = D2D1::Matrix3x2F::Translation(pos.X, pos.Y);
	auto Rz      = D2D1::Matrix3x2F::Rotation(-rot.Z);
	auto Sxy     = D2D1::Matrix3x2F::Scale(D2D1::SizeF(scl.X, scl.Y));
	auto TnegA   = D2D1::Matrix3x2F::Translation(-anchorX, -anchorY);

	auto world = Multiply(Multiply(Multiply(Multiply(Multiply(Tcenter, SflipY), Tpos), Rz), Sxy), TnegA);

	rt2d->BeginDraw();
	rt2d->SetTransform(world);
	rt2d->DrawTextLayout(D2D1::Point2F(0.f, 0.f), textLayout.Get(), brush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);
	rt2d->SetTransform(D2D1::Matrix3x2F::Identity());
	rt2d->EndDraw();
}

void AstrumTextRenderComponent::SetText(const std::wstring& t) {
	text = t;
	layoutDirty = true;
}
void AstrumTextRenderComponent::SetFont(const std::shared_ptr<AstrumTargetFont>& font) {
	targetFont = font;
	layoutDirty = true;
}
void AstrumTextRenderComponent::SetColor(const AstrumColor& c) {
	textColor = c;
	colorDirty = true;
}
void AstrumTextRenderComponent::SetAlignment(DWRITE_TEXT_ALIGNMENT horizontal, DWRITE_PARAGRAPH_ALIGNMENT vertical) {
	textAlign = horizontal;
	paragraphAlign = vertical;
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
void AstrumTextRenderComponent::SetPivot(float x, float y) {
	pivotX = x; pivotY = y;
	layoutDirty = true;
}
