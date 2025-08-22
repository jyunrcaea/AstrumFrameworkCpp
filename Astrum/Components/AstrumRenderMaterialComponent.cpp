#include "AstrumRenderMaterialComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"

namespace Astrum {
	void RenderMaterialComponent::PreRender() {
		if (nullptr == Material || nullptr == Mesh) return;

		Material->UpdateBuffer();
		RenderComponent::PreRender();
	}

	void RenderMaterialComponent::Render() {
		if (nullptr == Material) return;

		RenderComponent::Render();
		auto* const context = Renderer::Instance().GetContext();
		auto* const srv = Material->GetTexture()->GetShaderResourceView();
		context->PSSetShaderResources(0, 1, &srv);
		Mesh->Render();
	}

	std::shared_ptr<struct IShaderSetup> RenderMaterialComponent::GetDefaultShaderPipeline() const {
		return Renderer::Instance().DefaultTextureShaderPipeline;
	}

	void RenderMaterialComponent::SetupRectangleMesh(float width, float height, float z) {
		width /= 2;
		height /= 2;
		Mesh = TextureMesh::MakeShared({
			{ { -width, height, z }, { 0.0f, 0.0f } }, // 좌상단
			{ { width, height, z }, { 1.0f, 0.0f } }, // 우상단
			{ { -width, -height, z }, { 0.0f, 1.0f } }, // 좌하단
			{ { width, -height, z }, { 1.0f, 1.0f } }  // 우하단
			}, { 0, 1, 2, 1, 3, 2 });
	}

	void RenderMaterialComponent::SetupMeshFromTexture(float z) {
		Mesh = Material->CreateTextureSizeMesh(z);
	}
}