#pragma once
#include <memory>
#include "../Objects/AstrumObject.hpp"
#include "../Components/AstrumTextRenderComponent.hpp"

/// <summary>
/// 텍스트를 렌더링하는 게임 객체입니다.
/// 폰트, 텍스트 내용, 색상, 정렬, 줄바꿈 등을 설정할 수 있습니다.
/// 객체의 스케일에 따라 레이아웃 크기가 자동으로 조정됩니다.
/// </summary>
class AstrumTextObject : public AstrumObject {
public:
    /// <summary>
    /// 기본 텍스트 객체를 생성합니다.
    /// </summary>
    /// <param name="width">텍스트 레이아웃 너비입니다. 기본값은 200입니다.</param>
    /// <param name="height">텍스트 레이아웃 높이입니다. 기본값은 24입니다.</param>
    AstrumTextObject(float width = 200, float height = 24) : localLayoutWidth(width), localLayoutHeight(height) {
        AddComponent(textRenderer);
    }

    /// <summary>
    /// 텍스트와 폰트를 지정하여 텍스트 객체를 생성합니다.
    /// 레이아웃 크기는 폰트 크기와 텍스트 길이로 자동 계산됩니다.
    /// </summary>
    /// <typeparam name="TextType">std::wstring 타입입니다.</typeparam>
    /// <typeparam name="FontType">std::shared_ptr<AstrumTargetFont> 타입입니다.</typeparam>
    /// <param name="text">표시할 텍스트입니다.</param>
    /// <param name="font">사용할 폰트입니다.</param>
    template <typename TextType, typename FontType>
    requires (std::same_as<std::remove_cvref_t<TextType>, std::wstring> && std::same_as<std::remove_cvref_t<FontType>, std::shared_ptr<AstrumTargetFont>>)
    AstrumTextObject(TextType&& text, FontType&& font)
        : AstrumTextObject(std::forward<FontType>(font)->GetFontSize() * std::forward<TextType>(text).length(), std::forward<FontType>(font)->GetFontSize()) {
        textRenderer->SetText(std::forward<TextType>(text));
        textRenderer->SetFont(std::forward<FontType>(font));
    }

    /// <summary>
    /// 텍스트를 렌더링하는 컴포넌트를 반환합니다.
    /// </summary>
    /// <returns>텍스트 렌더 컴포넌트 공유 포인터입니다.</returns>
    std::shared_ptr<AstrumTextRenderComponent> GetTextRenderer() const { return textRenderer; }

    /// <summary>
    /// 표시할 텍스트를 설정합니다.
    /// </summary>
    /// <param name="t">설정할 텍스트입니다.</param>
    void SetText(const std::wstring& t) { textRenderer->SetText(t); }
    /// <summary>
    /// 표시할 텍스트를 설정합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="t">설정할 텍스트입니다.</param>
    void SetText(std::wstring&& t) { textRenderer->SetText(t); }
    /// <summary>
    /// 텍스트에 사용할 폰트를 설정합니다.
    /// </summary>
    /// <param name="f">설정할 폰트입니다.</param>
    void SetFont(const std::shared_ptr<AstrumTargetFont>& f) { textRenderer->SetFont(f); }
    /// <summary>
    /// 텍스트에 사용할 폰트를 설정합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="f">설정할 폰트입니다.</param>
    void SetFont(std::shared_ptr<AstrumTargetFont>&& f) { textRenderer->SetFont(f); }
    /// <summary>
    /// 텍스트의 색상을 설정합니다.
    /// </summary>
    /// <param name="c">설정할 색상입니다.</param>
    void SetColor(const AstrumColor& c) { textRenderer->SetColor(c); }
    /// <summary>
    /// 텍스트의 색상을 설정합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="c">설정할 색상입니다.</param>
    void SetColor(AstrumColor&& c) { textRenderer->SetColor(c); }
    /// <summary>
    /// 텍스트의 정렬 방식을 설정합니다.
    /// </summary>
    /// <param name="h">수평 정렬 방식입니다. (좌측, 중앙, 우측)</param>
    /// <param name="v">수직 정렬 방식입니다. (위, 중앙, 아래)</param>
    void SetAlignment(AstrumTextHorizontalAlignmentType h, AstrumTextVerticalAlignmentType v) { textRenderer->SetAlignment(h, v); }
    /// <summary>
    /// 텍스트의 줄바꿈 방식을 설정합니다.
    /// </summary>
    /// <param name="w">Direct Write 줄바꿈 방식입니다.</param>
    void SetWordWrapping(DWRITE_WORD_WRAPPING w) { textRenderer->SetWordWrapping(w); }
    
    /// <summary>
    /// 텍스트 레이아웃의 너비를 설정합니다.
    /// 이 값은 객체의 X축 스케일에 곱해져서 실제 렌더링 너비가 됩니다.
    /// </summary>
    /// <param name="width">설정할 레이아웃 너비입니다.</param>
    void SetLayoutWidth(float width) { localLayoutWidth = width; UpdateLayoutWidth(); }
    /// <summary>
    /// 텍스트 레이아웃의 높이를 설정합니다.
    /// 이 값은 객체의 Y축 스케일에 곱해져서 실제 렌더링 높이가 됩니다.
    /// </summary>
    /// <param name="height">설정할 레이아웃 높이입니다.</param>
    void SetLayoutHeight(float height) { localLayoutWidth = height; UpdateLayoutHeight(); }
    /// <summary>
    /// 텍스트 레이아웃의 너비를 반환합니다.
    /// </summary>
    /// <returns>레이아웃 너비입니다.</returns>
    float GetLayoutWidth() const { return localLayoutWidth; }
    /// <summary>
    /// 텍스트 레이아웃의 높이를 반환합니다.
    /// </summary>
    /// <returns>레이아웃 높이입니다.</returns>
    float GetLayoutHeight() const { return localLayoutWidth; }

protected:
    /// <summary>
    /// 절대 스케일이 변경될 때 호출됩니다.
    /// 레이아웃 크기를 스케일에 맞게 업데이트합니다.
    /// </summary>
    virtual void UpdateAbsoluteScale() override {
        AstrumObject::UpdateAbsoluteScale();
        UpdateLayoutWidth();
        UpdateLayoutHeight();
    }

private:
    /// <summary>
    /// 텍스트를 렌더링하는 컴포넌트입니다.
    /// </summary>
    std::shared_ptr<AstrumTextRenderComponent> textRenderer = std::make_shared<AstrumTextRenderComponent>();
    /// <summary>
    /// 로컬 좌표계에서의 레이아웃 너비입니다.
    /// 실제 렌더링 너비는 이 값에 절대 스케일 X를 곱한 값입니다.
    /// </summary>
    float localLayoutWidth = 200;
    /// <summary>
    /// 로컬 좌표계에서의 레이아웃 높이입니다.
    /// 실제 렌더링 높이는 이 값에 절대 스케일 Y를 곱한 값입니다.
    /// </summary>
    float localLayoutHeight = 20;
    /// <summary>
    /// 절대 스케일을 고려하여 렌더러의 너비를 업데이트합니다.
    /// </summary>
    void UpdateLayoutWidth() { textRenderer->SetWidth(GetAbsoluteScale().X * localLayoutWidth); }
    /// <summary>
    /// 절대 스케일을 고려하여 렌더러의 높이를 업데이트합니다.
    /// </summary>
    void UpdateLayoutHeight() { textRenderer->SetHeight(GetAbsoluteScale().Y * localLayoutHeight); }

public:
    /// <summary>
    /// 기본 설정으로 AstrumTextObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <returns>새로 생성된 AstrumTextObject 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumTextObject> MakeShared() { return std::make_shared<AstrumTextObject>(); }
    /// <summary>
    /// 텍스트와 폰트를 지정하여 AstrumTextObject의 공유 포인터를 생성합니다.
    /// </summary>
    /// <param name="text">표시할 텍스트입니다.</param>
    /// <param name="font">사용할 폰트입니다.</param>
    /// <returns>새로 생성된 AstrumTextObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumTextObject> MakeShared(const std::wstring& text, const std::shared_ptr<AstrumTargetFont>& font) {
        return std::make_shared<AstrumTextObject>(text, font);
	}
    /// <summary>
    /// 텍스트와 폰트를 지정하여 AstrumTextObject의 공유 포인터를 생성합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="text">표시할 텍스트입니다.</param>
    /// <param name="font">사용할 폰트입니다.</param>
    /// <returns>새로 생성된 AstrumTextObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumTextObject> MakeShared(std::wstring&& text, std::shared_ptr<AstrumTargetFont>&& font) {
        return std::make_shared<AstrumTextObject>(std::move(text), std::move(font));
    }
    /// <summary>
    /// 텍스트와 폰트를 지정하여 AstrumTextObject의 공유 포인터를 생성합니다. (혼합 참조 버전)
    /// </summary>
    /// <param name="text">표시할 텍스트입니다.</param>
    /// <param name="font">사용할 폰트입니다.</param>
    /// <returns>새로 생성된 AstrumTextObject 공유 포인터입니다.</returns>
    static std::shared_ptr<AstrumTextObject> MakeShared(std::wstring&& text, const std::shared_ptr<AstrumTargetFont>& font) {
        return std::make_shared<AstrumTextObject>(std::move(text), font);
    }
};

