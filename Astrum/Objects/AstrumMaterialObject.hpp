#pragma once
#include "AstrumObject.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Resources/AstrumMaterial.hpp"
#include "../Units/AstrumTextureVertex.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"

namespace Astrum
{
	class MaterialObject : public virtual Object, public virtual IMaterialObject
	{
	public:
		MaterialObject();
		// 텍스쳐를 통해 기본 머터리얼을 즉시 생성하고, 텍스쳐 크기에 알맞는 매쉬를 기본값으로 생성하여 할당합니다.
		MaterialObject(const std::shared_ptr<ITexture>& texture);
		MaterialObject(const std::shared_ptr<Material>& material, const std::shared_ptr<TextureMesh>& mesh = nullptr);

		virtual RenderMaterialComponent& GetRenderMaterialComponent() const noexcept override;

	protected:
		std::shared_ptr<RenderMaterialComponent> renderMaterialComponent = std::make_shared<RenderMaterialComponent>();

	#pragma region Override Object
	public:
		void Prepare() override { Object::Prepare(); }
		void Update() override { Object::Update(); }
		void Release() override { Object::Release(); }
		void Draw() override { Object::Draw(); }
		bool SetParent(IGroupObject* const p) override { return Object::SetParent(p); }
		bool ClearParent(IGroupObject* const p) override { return Object::ClearParent(p); }
		const Vector3& GetAbsolutePosition() override { return Object::GetAbsolutePosition(); }
		const Vector3& GetAbsoluteRotation() override { return Object::GetAbsoluteRotation(); }
		const Vector3& GetAbsoluteScale() override { return Object::GetAbsoluteScale(); }
		ObservedVector3& GetPosition() override { return Object::GetPosition(); }
		ObservedVector3& GetRotation() override { return Object::GetRotation(); }
		ObservedVector3& GetScale() override { return Object::GetScale(); }
		void SetPosition(const Vector3& pos) { Object::SetPosition(pos); }
		void SetRotation(const Vector3& rot) { Object::SetRotation(rot); }
		void SetScale(const Vector3& scale) { Object::SetScale(scale); }
		IComponentList& GetComponents() override { return Object::GetComponents(); }
		IGroupObject* GetParent() const override { return Object::GetParent(); }
	protected:
		void UpdateAbsolutePosition() override { Object::UpdateAbsolutePosition(); }
		void UpdateAbsoluteRotation() override { Object::UpdateAbsoluteRotation(); }
		void UpdateAbsoluteScale() override { Object::UpdateAbsoluteScale(); }
	public:
		bool IsPrepared() const override { return Object::IsPrepared(); }
		bool IsVisible() const override { return Object::IsVisible(); }
		void SetVisible(bool enable) override { Object::SetVisible(enable); }
	#pragma endregion
	};
}