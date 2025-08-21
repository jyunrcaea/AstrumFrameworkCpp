#include "AstrumMaterialObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Units/AstrumTextureVertex.hpp"

AstrumMaterialObject::AstrumMaterialObject() {
    AddComponent(renderMaterialComponent);
}
AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture) : AstrumMaterialObject() {
    renderMaterialComponent->Material = AstrumMaterial::MakeShared(texture);
    renderMaterialComponent->SetupMeshFromTexture();
}
AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, const std::shared_ptr<AstrumTextureMesh>& mesh) : AstrumMaterialObject() {
    renderMaterialComponent->Material = material;
    renderMaterialComponent->Mesh = mesh;
}

AstrumRenderMaterialComponent& AstrumMaterialObject::GetRenderMaterialComponent() const noexcept { return *renderMaterialComponent; }