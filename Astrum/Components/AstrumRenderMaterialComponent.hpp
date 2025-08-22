#pragma once
#include "../Components/AstrumRenderComponent.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Resources/AstrumMaterial.hpp"
#include "../Units/AstrumTextureVertex.hpp"

namespace Astrum {
	class ::Astrum::Material;
	class ::Astrum::TextureMesh;

	class RenderMaterialComponent : public RenderComponent
	{
	public:
		std::shared_ptr<::Astrum::Material> Material = nullptr;
		std::shared_ptr<::Astrum::TextureMesh> Mesh = nullptr;
		virtual std::shared_ptr<struct IShaderSetup> GetDefaultShaderPipeline() const override;

		//너비와 높이를 입력받고, 직사각형 매시를 생성하고 할당합니다.
		void SetupRectangleMesh(float width, float height, float z = 0.f);
		//머터리얼이 참조하는 텍스쳐의 크기대로 매시를 생성합니다.
		void SetupMeshFromTexture(float z = 0.f);

	protected:
		virtual void PreRender() override;
		virtual void Render() override;

	public:
		static std::shared_ptr<RenderMaterialComponent> MakeShared() {
			return std::make_shared<RenderMaterialComponent>();
		}
		static std::shared_ptr<RenderMaterialComponent> MakeShared(const std::shared_ptr<::Astrum::Material>& material) {
			auto component = std::make_shared<RenderMaterialComponent>();
			component->Material = material;
			return component;
		}
		static std::shared_ptr<RenderMaterialComponent> MakeShared(const std::shared_ptr<TextureMesh>& mesh) {
			auto component = std::make_shared<RenderMaterialComponent>();
			component->Mesh = mesh;
			return component;
		}
		static std::shared_ptr<RenderMaterialComponent> MakeShared(const std::shared_ptr<::Astrum::Material>& material, const std::shared_ptr<TextureMesh>& mesh) {
			auto component = std::make_shared<RenderMaterialComponent>();
			component->Material = material;
			component->Mesh = mesh;
			return component;
		}
		static std::shared_ptr<RenderMaterialComponent> MakeShared(std::shared_ptr<::Astrum::Material>&& material) {
			auto component = std::make_shared<RenderMaterialComponent>();
			component->Material = std::move(material);
			return component;
		}
		static std::shared_ptr<RenderMaterialComponent> MakeShared(std::shared_ptr<TextureMesh>&& mesh) {
			auto component = std::make_shared<RenderMaterialComponent>();
			component->Mesh = std::move(mesh);
			return component;
		}
		static std::shared_ptr<RenderMaterialComponent> MakeShared(std::shared_ptr<::Astrum::Material>&& material, std::shared_ptr<TextureMesh>&& mesh) {
			auto component = std::make_shared<RenderMaterialComponent>();
			component->Material = std::move(material);
			component->Mesh = std::move(mesh);
			return component;
		}
	};
}