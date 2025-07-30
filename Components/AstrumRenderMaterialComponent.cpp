#include "AstrumRenderMaterialComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"

void AstrumRenderMaterialComponent::PreRender() {
    if (nullptr == Material || nullptr == Mesh) return;

    Material->UpdateBuffer();
    AstrumRenderComponent::PreRender();
}

void AstrumRenderMaterialComponent::Render() {
    if (nullptr == Material) return;

    AstrumRenderComponent::Render();
    auto* const context = AstrumRenderer::Instance().GetContext();
    auto* const srv = Material->GetTexture()->GetShaderResourceView();
    context->PSSetShaderResources(0, 1, &srv);
    Mesh->Render();
}

std::shared_ptr<struct IAstrumShaderSetup> AstrumRenderMaterialComponent::GetDefaultShaderPipeline() const {
    return AstrumRenderer::Instance().DefaultTextureShaderPipeline;
}

void AstrumRenderMaterialComponent::SetupRectangleMesh(float width, float height, float z) {
    width /= 2;
    height /= 2;
    Mesh = AstrumTextureMesh::MakeShared({
        { { -width, height, z }, { 0.0f, 0.0f } }, // 좌상단
        { { width, height, z }, { 1.0f, 0.0f } }, // 우상단
        { { -width, -height, z }, { 0.0f, 1.0f } }, // 좌하단
        { { width, -height, z }, { 1.0f, 1.0f } }  // 우하단
    }, { 0, 1, 2, 1, 3, 2 });
}

void AstrumRenderMaterialComponent::SetupMeshFromTexture(float z) {
    Mesh = Material->CreateTextureSizeMesh(z);
}