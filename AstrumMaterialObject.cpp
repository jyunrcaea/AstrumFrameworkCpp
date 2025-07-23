#include "AstrumMaterialObject.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumTextureVertex.hpp"

namespace {
    constexpr std::vector<AstrumTextureVertex> CreateVertices(float width, float height) {
        width /= 2;
        height /= 2;

        return {
            { { -width,  height, 0.0f }, { 0.0f, 0.0f } }, // 좌상단
            { {  width,  height, 0.0f }, { 1.0f, 0.0f } }, // 우상단
            { { -width, -height, 0.0f }, { 0.0f, 1.0f } }, // 좌하단
            { {  width, -height, 0.0f }, { 1.0f, 1.0f } }  // 우하단
        };
    }
}

AstrumMaterialObject::AstrumMaterialObject()
    : material(nullptr), mesh(CreateVertices(1,1), { 0, 1, 2, 1, 3, 2 }, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT)
{
}

AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture)
    : AstrumMaterialObject(std::make_shared<AstrumMaterial>(texture)) { }

AstrumMaterialObject::AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, float width, float height)
    : material(material), mesh(CreateVertices(width, height), { 0, 1, 2, 1, 3, 2 }, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT)
{
}

void AstrumMaterialObject::Render() {
    if (nullptr == material) return;

    AstrumDrawableObject::Render();
    auto* const context = AstrumRenderer::Instance().GetContext();
    auto* const srv = material->GetTexture().GetShaderResourceView();
    context->PSSetShaderResources(0, 1, &srv);
    mesh.Render();
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

AstrumMaterial& AstrumMaterialObject::GetMaterial() const { return *material; }
void AstrumMaterialObject::SetMaterial(const std::shared_ptr<AstrumMaterial>& material) { this->material = material; }
void AstrumMaterialObject::SetMaterial(std::shared_ptr<AstrumMaterial>&& material) { this->material = std::move(material); }
