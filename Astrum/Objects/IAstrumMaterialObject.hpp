#pragma once
#include <memory>
#include "../Resources/AstrumMaterial.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"

namespace Astrum {
	class RenderMaterialComponent;

	struct IMaterialObject : public virtual IObject
	{
		virtual RenderMaterialComponent& GetRenderMaterialComponent() const = 0;

		std::shared_ptr<class Material> GetMaterial() const;
		void SetMaterial(const std::shared_ptr<Material>& material);
		std::shared_ptr<class TextureMesh> GetTextureMesh() const;
		void SetTextureMesh(const std::shared_ptr<class TextureMesh>& mesh);
		std::shared_ptr<ITexture> GetTexture() const;
	};
}