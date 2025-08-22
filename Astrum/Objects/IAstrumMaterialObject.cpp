#include "IAstrumMaterialObject.hpp"

namespace Astrum {
	std::shared_ptr<Material> IMaterialObject::GetMaterial() const
	{
		return GetRenderMaterialComponent().Material;
	}

	void IMaterialObject::SetMaterial(const std::shared_ptr<Material>& material)
	{
		GetRenderMaterialComponent().Material = material;
	}

	std::shared_ptr<TextureMesh> IMaterialObject::GetTextureMesh() const
	{
		return GetRenderMaterialComponent().Mesh;
	}

	void IMaterialObject::SetTextureMesh(const std::shared_ptr<class TextureMesh>& mesh)
	{
		GetRenderMaterialComponent().Mesh = mesh;
	}

	std::shared_ptr<ITexture> IMaterialObject::GetTexture() const {
		return GetMaterial()->GetTexture();
	}
}