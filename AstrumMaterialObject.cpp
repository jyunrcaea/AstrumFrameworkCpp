#include "AstrumMaterialObject.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumTextureVertex.hpp"

AstrumMaterialObject::AstrumMaterialObject() { }
AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture)
    : material(AstrumMaterial::MakeShared(texture)) {
    CreateToSetTextureMesh2D(
        static_cast<float>(texture->GetWidth()),
        static_cast<float>(texture->GetHeight())
    );
}
AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, const std::shared_ptr<AstrumTextureMesh>& mesh)
    : material(material), mesh(mesh) { }
AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumTextureMesh>& mesh, const std::shared_ptr<AstrumMaterial>& material )
    : material(material), mesh(mesh) { }

void AstrumMaterialObject::Render() {
    if (nullptr == material) return;

    AstrumDrawableObject::Render();
    auto* const context = AstrumRenderer::Instance().GetContext();
    auto* const srv = material->GetTexture()->GetShaderResourceView();
    context->PSSetShaderResources(0, 1, &srv);
    mesh->Render();
}

void AstrumMaterialObject::PreRender()
{
    if (nullptr == material) return;

    material->UpdateBuffer();
    AstrumDrawableObject::PreRender();
}

std::shared_ptr<struct IAstrumShaderPipeline> AstrumMaterialObject::GetDefaultShaderPipeline() const
{
    return AstrumRenderer::Instance().DefaultTextureShaderPipeline;
}

std::shared_ptr<AstrumMaterial> AstrumMaterialObject::GetMaterial() { return material; }
void AstrumMaterialObject::SetMaterial(const std::shared_ptr<AstrumMaterial>& material) { this->material = material; }
void AstrumMaterialObject::SetMaterial(std::shared_ptr<AstrumMaterial>&& material) { this->material = std::move(material); }

std::shared_ptr<AstrumTextureMesh> AstrumMaterialObject::GetTextureMesh() { return mesh; }
void AstrumMaterialObject::SetTextureMesh(const std::shared_ptr<AstrumTextureMesh>& mesh) { this->mesh = mesh; }
void AstrumMaterialObject::SetTextureMesh(std::shared_ptr<AstrumTextureMesh>&& mesh) { this->mesh = std::move(mesh); }

void AstrumMaterialObject::CreateToSetTextureMesh2D(float width, float height, float z)
{
    width /= 2;
    height /= 2;
    mesh = AstrumTextureMesh::MakeShared({
        { { -width,  height, z }, { 0.0f, 0.0f } }, // 좌상단
        { {  width,  height, z }, { 1.0f, 0.0f } }, // 우상단
        { { -width, -height, z }, { 0.0f, 1.0f } }, // 좌하단
        { {  width, -height, z }, { 1.0f, 1.0f } }  // 우하단
    }, { 0, 1, 2, 1, 3, 2 });
}