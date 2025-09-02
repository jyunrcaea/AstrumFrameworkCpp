#include "IAstrumMaterialObject.hpp"

std::shared_ptr<AstrumMaterial> IAstrumMaterialObject::GetMaterial() const {
	return GetRenderMaterialComponent().Material;
}

void IAstrumMaterialObject::SetMaterial(const std::shared_ptr<AstrumMaterial>& material) {
	GetRenderMaterialComponent().Material = material;
}

void IAstrumMaterialObject::SetMaterial(std::shared_ptr<AstrumMaterial>&& material) {
	GetRenderMaterialComponent().Material = std::move(material);
}

std::shared_ptr<AstrumTextureMesh> IAstrumMaterialObject::GetTextureMesh() const {
	return GetRenderMaterialComponent().Mesh;
}

void IAstrumMaterialObject::SetTextureMesh(const std::shared_ptr<AstrumTextureMesh>& mesh) {
	GetRenderMaterialComponent().Mesh = mesh;
}
void IAstrumMaterialObject::SetTextureMesh(std::shared_ptr<class AstrumTextureMesh>&& mesh) {
	GetRenderMaterialComponent().Mesh = std::move(mesh);
}

std::shared_ptr<IAstrumTexture> IAstrumMaterialObject::GetTexture() const {
	return GetMaterial()->GetTexture();
}