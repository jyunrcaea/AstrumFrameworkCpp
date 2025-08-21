#include "IAstrumMaterialObject.hpp"

std::shared_ptr<AstrumMaterial> IAstrumMaterialObject::GetMaterial() const
{
    return GetRenderMaterialComponent().Material;
}

void IAstrumMaterialObject::SetMaterial(const std::shared_ptr<AstrumMaterial>& material)
{
	GetRenderMaterialComponent().Material = material;
}

std::shared_ptr<AstrumTextureMesh> IAstrumMaterialObject::GetTextureMesh() const
{
	return GetRenderMaterialComponent().Mesh;
}

void IAstrumMaterialObject::SetTextureMesh(const std::shared_ptr<AstrumTextureMesh>& mesh)
{
	GetRenderMaterialComponent().Mesh = mesh;
}

std::shared_ptr<AstrumTexture> IAstrumMaterialObject::GetTexture() const { 
	return GetMaterial()->GetTexture();
}