#include "AstrumMaterialObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Units/AstrumTextureVertex.hpp"

namespace Astrum
{
	MaterialObject::MaterialObject() {
		AddComponent(renderMaterialComponent);
	}
	MaterialObject::MaterialObject(const std::shared_ptr<ITexture>& texture) : MaterialObject() {
		renderMaterialComponent->Material = Material::MakeShared(texture);
		renderMaterialComponent->SetupMeshFromTexture();
	}
	MaterialObject::MaterialObject(const std::shared_ptr<Material>& material, const std::shared_ptr<TextureMesh>& mesh) : MaterialObject() {
		renderMaterialComponent->Material = material;
		renderMaterialComponent->Mesh = mesh;
	}

	RenderMaterialComponent& MaterialObject::GetRenderMaterialComponent() const noexcept { return *renderMaterialComponent; }
}