#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <memory>

class AstrumFonts;

/// <summary>
/// DirectWrite 텍스트 포맷을 래핑하는 글꼴 클래스입니다.
/// AstrumFonts에서 생성되며, 특정 크기와 스타일의 글꼴을 나타냅니다.
/// 텍스트 레이아웃 생성 및 렌더링에 사용됩니다.
/// </summary>
class AstrumTargetFont
{
	friend class AstrumFonts;

public:
	/// <summary>
	/// DirectWrite 텍스트 포맷을 사용하여 대상 글꼴을 생성합니다.
	/// </summary>
	/// <param name="factory">DirectWrite 팩토리입니다.</param>
	/// <param name="textFormat">DirectWrite 텍스트 포맷입니다.</param>
	/// <param name="fontSize">글꼴 크기(포인트)입니다.</param>
	AstrumTargetFont(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat, float fontSize)
		: writeFactory(factory), textFormat(textFormat), fontSize(fontSize) {}

	/// <summary>
	/// 내부 DirectWrite 텍스트 포맷 객체에 접근합니다.
	/// 고급 DirectWrite 기능을 사용할 때 필요합니다.
	/// </summary>
	/// <returns>IDWriteTextFormat 포인터입니다.</returns>
	IDWriteTextFormat* GetTextFormat() const { return textFormat.Get(); }
	/// <summary>
	/// 주어진 텍스트와 레이아웃 경계에 대한 DirectWrite 텍스트 레이아웃을 생성합니다.
	/// </summary>
	/// <param name="text">레이아웃할 텍스트입니다.</param>
	/// <param name="layoutWidth">레이아웃 너비입니다. 0이면 자동/제한 없음입니다.</param>
	/// <param name="layoutHeight">레이아웃 높이입니다. 0이면 자동/제한 없음입니다.</param>
	/// <returns>생성된 IDWriteTextLayout COM 포인터입니다.</returns>
	Microsoft::WRL::ComPtr<IDWriteTextLayout> CreateTextLayout(const std::wstring& text, float layoutWidth, float layoutHeight) const;

	/// <summary>
	/// 이 글꼴의 크기를 반환합니다.
	/// </summary>
	/// <returns>글꼴 크기(포인트)입니다.</returns>
	float GetFontSize() const { return fontSize;  }
	/// <summary>
	/// 이 글꼴의 크기를 설정합니다.
	/// </summary>
	/// <param name="newFontSize">설정할 글꼴 크기(포인트)입니다.</param>
	void SetFontSize(float newFontSize) { fontSize = newFontSize; }
private:
	/// <summary>
	/// DirectWrite 팩토리입니다.
	/// 텍스트 레이아웃 생성에 사용됩니다.
	/// </summary>
	const Microsoft::WRL::ComPtr<IDWriteFactory5> writeFactory;
	/// <summary>
	/// DirectWrite 텍스트 포맷입니다.
	/// 글꼴 이름, 크기, 정렬, 줄바꿈 등의 속성을 포함합니다.
	/// </summary>
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;
	/// <summary>
	/// 글꼴 크기(포인트)입니다.
	/// 기본값은 12입니다.
	/// </summary>
	float fontSize = 12.f;

public:
	/// <summary>
	/// DirectWrite 텍스트 포맷을 사용하여 AstrumTargetFont의 공유 포인터를 생성합니다.
	/// </summary>
	/// <param name="factory">DirectWrite 팩토리입니다.</param>
	/// <param name="textFormat">DirectWrite 텍스트 포맷입니다.</param>
	/// <param name="fontSize">글꼴 크기(포인트)입니다.</param>
	/// <returns>새로 생성된 AstrumTargetFont 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTargetFont> MakeShared(const Microsoft::WRL::ComPtr<IDWriteFactory5>& factory, Microsoft::WRL::ComPtr<IDWriteTextFormat>&& textFormat, float fontSize) {
		return std::make_shared<AstrumTargetFont>(factory, std::move(textFormat), fontSize);
	}
};