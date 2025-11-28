#pragma once
#include <memory>
#include <string>
#include <wrl/client.h>
#include <d2d1.h>
#include <dwrite_3.h>
#include "AstrumComponent.hpp"
#include "../Resources/AstrumTargetFont.hpp"
#include "../Graphics/IAstrumRenderable.hpp"
#include "../Units/AstrumColor.hpp"
#include "../Enums/AstrumTextAlignmentType.hpp"

/// <summary>
/// Direct2D와 DirectWrite를 사용하여 텍스트를 렌더링하는 컴포넌트입니다.
/// </summary>
class AstrumTextRenderComponent : public AstrumComponent, public IAstrumRenderable
{
public:
	/// <summary>
	/// 텍스트 렌더 컴포넌트를 생성합니다.
	/// </summary>
	AstrumTextRenderComponent();
	/// <summary>
	/// 텍스트를 그립니다.
	/// </summary>
	virtual void Draw() override;

protected:
	/// <summary>
	/// 렌더링 전 준비 작업을 수행합니다. 내부 레이아웃을 재구성합니다.
	/// </summary>
	virtual void PreRender() override;
	/// <summary>
	/// 텍스트를 렌더링합니다.
	/// </summary>
	virtual void Render() override;

public:
	/// <summary>
	/// 텍스트를 설정합니다.
	/// </summary>
	/// <typeparam name="T">std::wstring 타입입니다.</typeparam>
	/// <param name="newText">설정할 텍스트입니다.</param>
	template <typename T>
	requires std::same_as<std::remove_cvref_t<T>, std::wstring>
	void SetText(T&& newText);
	/// <summary>
	/// 텍스트에 사용할 폰트를 설정합니다.
	/// </summary>
	/// <typeparam name="T">std::shared_ptr&lt;AstrumTargetFont&gt; 타입입니다.</typeparam>
	/// <param name="newFont">설정할 폰트입니다.</param>
	template <typename T>
	requires std::same_as<std::remove_cvref_t<T>, std::shared_ptr<AstrumTargetFont>>
	void SetFont(T&& newFont);
	/// <summary>
	/// 텍스트의 색상을 설정합니다.
	/// </summary>
	/// <typeparam name="T">AstrumColor 타입입니다.</typeparam>
	/// <param name="newTextColor">설정할 색상입니다.</param>
	template <typename T>
	requires std::same_as<std::remove_cvref_t<T>, AstrumColor>
	void SetColor(T&& newTextColor);
	/// <summary>
	/// 텍스트의 정렬 방식을 설정합니다.
	/// </summary>
	/// <param name="horizontal">수평 정렬 방식입니다.</param>
	/// <param name="vertical">수직 정렬 방식입니다.</param>
	void SetAlignment(AstrumTextHorizontalAlignmentType horizontal, AstrumTextVerticalAlignmentType vertical);
	/// <summary>
	/// 텍스트의 줄바꿈 방식을 설정합니다.
	/// </summary>
	/// <param name="wrap">줄바꿈 방식입니다.</param>
	void SetWordWrapping(DWRITE_WORD_WRAPPING wrap);
	/// <summary>
	/// 텍스트 레이아웃의 크기를 설정합니다.
	/// 0은 해당 축에서 제한이 없음(줄바꿈 없음)을 의미합니다.
	/// </summary>
	/// <param name="width">레이아웃의 너비입니다.</param>
	/// <param name="height">레이아웃의 높이입니다.</param>
	void SetLayoutSize(float width, float height);

	/// <summary>
	/// 현재 텍스트를 반환합니다.
	/// </summary>
	/// <returns>현재 텍스트 참조입니다.</returns>
	const std::wstring& GetText() const { return text; }
	/// <summary>
	/// 현재 폰트를 반환합니다.
	/// </summary>
	/// <returns>현재 폰트 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumTargetFont> GetFont() const { return targetFont; }
	/// <summary>
	/// 현재 텍스트 색상을 반환합니다.
	/// </summary>
	/// <returns>현재 텍스트 색상입니다.</returns>
	AstrumColor GetColor() const { return textColor; }

	/// <summary>
	/// 텍스트 레이아웃의 너비를 반환합니다.
	/// </summary>
	/// <returns>레이아웃의 너비입니다.</returns>
	float GetWidth() const { return layoutWidth; }
	/// <summary>
	/// 텍스트 레이아웃의 높이를 반환합니다.
	/// </summary>
	/// <returns>레이아웃의 높이입니다.</returns>
	float GetHeight() const { return layoutHeight; }
	/// <summary>
	/// 텍스트 레이아웃의 너비를 설정합니다.
	/// </summary>
	/// <param name="newWidth">설정할 너비입니다.</param>
	void SetWidth(float newWidth) { layoutWidth = newWidth; }
	/// <summary>
	/// 텍스트 레이아웃의 높이를 설정합니다.
	/// </summary>
	/// <param name="newHeight">설정할 높이입니다.</param>
	void SetHeight(float newHeight) { layoutHeight = newHeight; }

private:
	/// <summary>
	/// 텍스트에 사용할 폰트입니다.
	/// </summary>
	std::shared_ptr<AstrumTargetFont> targetFont = nullptr;
	/// <summary>
	/// 렌더링할 텍스트입니다.
	/// </summary>
	std::wstring text;
	/// <summary>
	/// 텍스트의 색상입니다. 기본값은 검은색입니다.
	/// </summary>
	AstrumColor textColor = AstrumColor::Black;
	/// <summary>
	/// 텍스트 레이아웃의 너비입니다. 기본값은 400.0f입니다.
	/// </summary>
	float layoutWidth = 400.f;
	/// <summary>
	/// 텍스트 레이아웃의 높이입니다. 기본값은 100.0f입니다.
	/// </summary>
	float layoutHeight = 100.f;
	/// <summary>
	/// 텍스트의 수평 정렬 방식입니다. 기본값은 CENTER입니다.
	/// </summary>
	DWRITE_TEXT_ALIGNMENT textAlign = DWRITE_TEXT_ALIGNMENT_CENTER;
	/// <summary>
	/// 텍스트의 수직 정렬 방식입니다. 기본값은 CENTER입니다.
	/// </summary>
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlign = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	/// <summary>
	/// 텍스트의 줄바꿈 방식입니다. 기본값은 WRAP입니다.
	/// </summary>
	DWRITE_WORD_WRAPPING wordWrapping = DWRITE_WORD_WRAPPING_WRAP;

	/// <summary>
	/// Direct2D 고체 색상 브러시입니다. 텍스트 색상 렌더링에 사용됩니다.
	/// </summary>
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush = nullptr;
	/// <summary>
	/// DirectWrite 텍스트 레이아웃입니다. 텍스트 포맷팅에 사용됩니다.
	/// </summary>
	Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
	/// <summary>
	/// 레이아웃이 재구성되어야 함을 나타내는 플래그입니다.
	/// </summary>
	bool layoutDirty = true;
	/// <summary>
	/// 색상이 업데이트되어야 함을 나타내는 플래그입니다.
	/// </summary>
	bool colorDirty = true;

public:
	/// <summary>
	/// AstrumTextRenderComponent 객체의 공유 포인터를 생성합니다.
	/// </summary>
	/// <returns>새로 생성된 AstrumTextRenderComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTextRenderComponent> MakeShared() { return std::make_shared<AstrumTextRenderComponent>(); }
	/// <summary>
	/// AstrumTextRenderComponent 객체의 공유 포인터를 생성합니다. (텍스트와 폰트 지정)
	/// </summary>
	/// <param name="text">설정할 텍스트입니다.</param>
	/// <param name="font">설정할 폰트입니다.</param>
	/// <returns>새로 생성된 AstrumTextRenderComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTextRenderComponent> MakeShared(const std::wstring& text, const std::shared_ptr<AstrumTargetFont>& font) {
		auto instance = std::make_shared<AstrumTextRenderComponent>();
		instance->SetText(text);
		instance->SetFont(font);
		return instance;
	}
	/// <summary>
	/// AstrumTextRenderComponent 객체의 공유 포인터를 생성합니다. (텍스트와 폰트 지정, 우측값 참조 버전)
	/// </summary>
	/// <param name="text">설정할 텍스트입니다.</param>
	/// <param name="font">설정할 폰트입니다.</param>
	/// <returns>새로 생성된 AstrumTextRenderComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTextRenderComponent> MakeShared(std::wstring&& text, std::shared_ptr<AstrumTargetFont>&& font) {
		auto instance = std::make_shared<AstrumTextRenderComponent>();
		instance->SetText(std::move(text));
		instance->SetFont(std::move(font));
		return instance;
	}
	/// <summary>
	/// AstrumTextRenderComponent 객체의 공유 포인터를 생성합니다. (텍스트와 폰트 지정, 혼합 참조 버전 1)
	/// </summary>
	/// <param name="text">설정할 텍스트입니다.</param>
	/// <param name="font">설정할 폰트입니다.</param>
	/// <returns>새로 생성된 AstrumTextRenderComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTextRenderComponent> MakeShared(const std::wstring& text, std::shared_ptr<AstrumTargetFont>&& font) {
		auto instance = std::make_shared<AstrumTextRenderComponent>();
		instance->SetText(text);
		instance->SetFont(std::move(font));
		return instance;
	}
	/// <summary>
	/// AstrumTextRenderComponent 객체의 공유 포인터를 생성합니다. (텍스트와 폰트 지정, 혼합 참조 버전 2)
	/// </summary>
	/// <param name="text">설정할 텍스트입니다.</param>
	/// <param name="font">설정할 폰트입니다.</param>
	/// <returns>새로 생성된 AstrumTextRenderComponent 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTextRenderComponent> MakeShared(std::wstring&& text, const std::shared_ptr<AstrumTargetFont>& font) {
		auto instance = std::make_shared<AstrumTextRenderComponent>();
		instance->SetText(std::move(text));
		instance->SetFont(font);
		return instance;
	}
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