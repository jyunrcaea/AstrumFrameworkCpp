#pragma once
#include "AstrumDrawableObject.hpp"
#include "AstrumMesh.hpp"
#include "AstrumMaterial.hpp"
#include "AstrumTextureVertex.hpp"
#include "IAstrumMaterialObject.h"

class AstrumMaterialObject : public AstrumDrawableObject, public IAstrumMaterialObject
{
public:
    AstrumMaterialObject();
    AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture);
    AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, float width = 1.0f, float height = 1.0f);

protected:
    virtual void Render() override;
    virtual void PreRender() override;
    virtual std::shared_ptr<struct IAstrumShaderPipeline> GetDefaultShaderPipeline() const override;

    AstrumMaterial& GetMaterial() const;
    void SetMaterial(const std::shared_ptr<AstrumMaterial>& material);
    void SetMaterial(std::shared_ptr<AstrumMaterial>&& material);
private:
    std::shared_ptr<AstrumMaterial> material;
    AstrumMesh<AstrumTextureVertex> mesh;
};