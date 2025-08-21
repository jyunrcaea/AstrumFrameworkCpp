#pragma once
#include "AstrumObject.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Resources/AstrumMaterial.hpp"
#include "../Units/AstrumTextureVertex.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"

class AstrumMaterialObject : public virtual AstrumObject, public virtual IAstrumMaterialObject
{
public:
    AstrumMaterialObject();
    // 텍스쳐를 통해 기본 머터리얼을 즉시 생성하고, 텍스쳐 크기에 알맞는 매쉬를 기본값으로 생성하여 할당합니다.
    AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture);
    AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, const std::shared_ptr<AstrumTextureMesh>& mesh = nullptr);

    virtual AstrumRenderMaterialComponent& GetRenderMaterialComponent() const noexcept override;

protected:
    std::shared_ptr<AstrumRenderMaterialComponent> renderMaterialComponent = std::make_shared<AstrumRenderMaterialComponent>();

#pragma region Override AstrumObject
public:
    void Prepare() override { AstrumObject::Prepare(); }
    void Update() override { AstrumObject::Update(); }
    void Release() override { AstrumObject::Release(); }
    void Draw() override { AstrumObject::Draw(); }
    bool SetParent(IAstrumGroupObject* const p) override { return AstrumObject::SetParent(p); }
    bool ClearParent(IAstrumGroupObject* const p) override { return AstrumObject::ClearParent(p); }
	const AstrumVector3& GetAbsolutePosition() override { return AstrumObject::GetAbsolutePosition(); }
    const AstrumVector3& GetAbsoluteRotation() override { return AstrumObject::GetAbsoluteRotation(); }
    const AstrumVector3& GetAbsoluteScale() override { return AstrumObject::GetAbsoluteScale(); }
    AstrumObservedVector3& GetPosition() override { return AstrumObject::GetPosition(); }
    AstrumObservedVector3& GetRotation() override { return AstrumObject::GetRotation(); }
    AstrumObservedVector3& GetScale() override { return AstrumObject::GetScale(); }
    void SetPosition(const AstrumVector3& pos) { AstrumObject::SetPosition(pos); }
    void SetRotation(const AstrumVector3& rot) { AstrumObject::SetRotation(rot); }
	void SetScale(const AstrumVector3& scale) { AstrumObject::SetScale(scale); }
	IAstrumComponentList& GetComponents() override { return AstrumObject::GetComponents(); }
	IAstrumGroupObject* GetParent() const override { return AstrumObject::GetParent(); }
protected:
    void UpdateAbsolutePosition() override { AstrumObject::UpdateAbsolutePosition(); }
    void UpdateAbsoluteRotation() override { AstrumObject::UpdateAbsoluteRotation(); }
    void UpdateAbsoluteScale() override { AstrumObject::UpdateAbsoluteScale(); }
public:
    bool IsPrepared() const override { return AstrumObject::IsPrepared(); }
    bool IsVisible() const override { return AstrumObject::IsVisible(); }
    void SetVisible(bool enable) override { AstrumObject::SetVisible(enable); }
#pragma endregion
};