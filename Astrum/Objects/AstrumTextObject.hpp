#pragma once
#include "../Objects/AstrumObject.hpp"
#include "../Components/AstrumTextRenderComponent.hpp"

// 텍스트를 그리는 객체
class AstrumTextObject : public AstrumObject {
public:
    AstrumTextObject(float width = 200, float height = 24) : localLayoutWidth(width), localLayoutHeight(height) {
        AddComponent(textRenderer);
    }

    template <typename TextType, typename FontType>
    requires (std::same_as<std::remove_cvref_t<TextType>, std::wstring> && std::same_as<std::remove_cvref_t<FontType>, std::shared_ptr<AstrumTargetFont>>)
    AstrumTextObject(TextType&& text, FontType&& font)
        : AstrumTextObject(std::forward<FontType>(font)->GetFontSize() * std::forward<TextType>(text).length(), std::forward<FontType>(font)->GetFontSize()) {
        textRenderer->SetText(std::forward<TextType>(text));
        textRenderer->SetFont(std::forward<FontType>(font));
    }

    std::shared_ptr<AstrumTextRenderComponent> GetTextRenderer() const { return textRenderer; }

    void SetText(const std::wstring& t) { textRenderer->SetText(t); }
    void SetText(std::wstring&& t) { textRenderer->SetText(t); }
    void SetFont(const std::shared_ptr<AstrumTargetFont>& f) { textRenderer->SetFont(f); }
    void SetFont(std::shared_ptr<AstrumTargetFont>&& f) { textRenderer->SetFont(f); }
    void SetColor(const AstrumColor& c) { textRenderer->SetColor(c); }
    void SetColor(AstrumColor&& c) { textRenderer->SetColor(c); }
    void SetAlignment(AstrumTextHorizontalAlignmentType h, AstrumTextVerticalAlignmentType v) { textRenderer->SetAlignment(h, v); }
    void SetWordWrapping(DWRITE_WORD_WRAPPING w) { textRenderer->SetWordWrapping(w); }
    
    void SetLayoutWidth(float width) { localLayoutWidth = width; UpdateLayoutWidth(); }
    void SetLayoutHeight(float height) { localLayoutWidth = height; UpdateLayoutHeight(); }
    float GetLayoutWidth() const { return localLayoutWidth; }
    float GetLayoutHeight() const { return localLayoutWidth; }

public:
    static std::shared_ptr<AstrumTextObject> MakeShared() { return std::make_shared<AstrumTextObject>(); }
    static std::shared_ptr<AstrumTextObject> MakeShared(const std::wstring& text, const std::shared_ptr<AstrumTargetFont>& font) {
        return std::make_shared<AstrumTextObject>(text, font);
    }
    static std::shared_ptr<AstrumTextObject> MakeShared(std::wstring&& text, std::shared_ptr<AstrumTargetFont>&& font) {
        return std::make_shared<AstrumTextObject>(std::move(text), std::move(font));
    }

protected:
    virtual void UpdateAbsoluteScale() override {
        AstrumObject::UpdateAbsoluteScale();
        UpdateLayoutWidth();
        UpdateLayoutHeight();
    }

private:
    std::shared_ptr<AstrumTextRenderComponent> textRenderer = std::make_shared<AstrumTextRenderComponent>();
    float localLayoutWidth, localLayoutHeight;
    void UpdateLayoutWidth() { textRenderer->SetWidth(GetAbsoluteScale().X * localLayoutWidth); }
    void UpdateLayoutHeight() { textRenderer->SetHeight(GetAbsoluteScale().Y * localLayoutHeight); }
};

