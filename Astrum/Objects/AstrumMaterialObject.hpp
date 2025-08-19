#pragma once
#include "AstrumObject.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Resources/AstrumMaterial.hpp"
#include "../Units/AstrumTextureVertex.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"

class AstrumMaterialObject : public AstrumObject, public IAstrumMaterialObject
{
public:
    AstrumMaterialObject();
    // 텍스쳐를 통해 기본 머터리얼을 즉시 생성하고, 텍스쳐 크기에 알맞는 매쉬를 기본값으로 생성하여 할당합니다.
    AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture);
    AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, const std::shared_ptr<AstrumTextureMesh>& mesh = nullptr);

    virtual std::shared_ptr<AstrumRenderMaterialComponent> GetRenderMaterialComponent() const override;

protected:
    std::shared_ptr<AstrumRenderMaterialComponent> renderMaterialComponent = std::make_shared<AstrumRenderMaterialComponent>();
};