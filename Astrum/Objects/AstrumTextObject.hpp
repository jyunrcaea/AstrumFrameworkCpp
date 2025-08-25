#pragma once
#include "../Objects/AstrumObject.hpp"
#include "../Components/AstrumTextRenderComponent.hpp"

// Lightweight object that exposes a text renderer component for easy use
class AstrumTextObject : public AstrumObject {
public:
    AstrumTextObject() {
        AddComponent(textRenderer);
    }
    AstrumTextObject(const std::wstring& text, const std::shared_ptr<AstrumTargetFont>& font) : AstrumTextObject() {
        textRenderer->SetText(text);
        textRenderer->SetFont(font);
    }

    std::shared_ptr<AstrumTextRenderComponent> GetTextRenderer() const { return textRenderer; }

    // convenience forwarders
    void SetText(const std::wstring& t) { textRenderer->SetText(t); }
    void SetFont(const std::shared_ptr<AstrumTargetFont>& f) { textRenderer->SetFont(f); }
    void SetColor(const AstrumColor& c) { textRenderer->SetColor(c); }
    void SetAlignment(DWRITE_TEXT_ALIGNMENT h, DWRITE_PARAGRAPH_ALIGNMENT v) { textRenderer->SetAlignment(h, v); }
    void SetWordWrapping(DWRITE_WORD_WRAPPING w) { textRenderer->SetWordWrapping(w); }
    void SetLayoutSize(float w, float h) { textRenderer->SetLayoutSize(w, h); }
    void SetPivot(float x, float y) { textRenderer->SetPivot(x, y); }

public:
    static std::shared_ptr<AstrumTextObject> MakeShared() { return std::make_shared<AstrumTextObject>(); }
    static std::shared_ptr<AstrumTextObject> MakeShared(const std::wstring& text, const std::shared_ptr<AstrumTargetFont>& font) {
        return std::make_shared<AstrumTextObject>(text, font);
    }

private:
    std::shared_ptr<AstrumTextRenderComponent> textRenderer = std::make_shared<AstrumTextRenderComponent>();
};

