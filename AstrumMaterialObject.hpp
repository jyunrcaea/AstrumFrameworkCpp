#pragma once
#include "AstrumDrawableObject.hpp"
#include "AstrumTextureMesh.hpp"
#include "AstrumMaterial.hpp"
#include "AstrumTextureVertex.hpp"
#include "IAstrumMaterialObject.hpp"

class AstrumMaterialObject : public AstrumDrawableObject, public IAstrumMaterialObject
{
public:
    AstrumMaterialObject();
    // 텍스쳐를 통해 기본 머터리얼을 즉시 생성하고, 텍스쳐 크기에 알맞는 매쉬를 기본값으로 생성하여 할당합니다.
    AstrumMaterialObject(const std::shared_ptr<AstrumTexture>& texture);
    AstrumMaterialObject(const std::shared_ptr<AstrumMaterial>& material, const std::shared_ptr<AstrumTextureMesh>& mesh = nullptr);
    AstrumMaterialObject(const std::shared_ptr<AstrumTextureMesh>& mesh, const std::shared_ptr<AstrumMaterial>& material = nullptr);

protected:
    virtual void Render() override;
    virtual void PreRender() override;
    virtual std::shared_ptr<struct IAstrumShaderPipeline> GetDefaultShaderPipeline() const override;

    virtual std::shared_ptr<AstrumMaterial> GetMaterial() override;
    virtual void SetMaterial(const std::shared_ptr<AstrumMaterial>& material) override;
    void SetMaterial(std::shared_ptr<AstrumMaterial>&& material);

    std::shared_ptr<AstrumTextureMesh> GetTextureMesh();
    void SetTextureMesh(const std::shared_ptr<AstrumTextureMesh>& mesh);
    void SetTextureMesh(std::shared_ptr<AstrumTextureMesh>&& mesh);
    //너비와 높이를 입력받고, 직사각형 매시를 생성하고 할당합니다.
    void CreateToSetTextureMesh2D(float width, float height, float z = 0.f);
private:
    std::shared_ptr<AstrumMaterial> material = nullptr;
    std::shared_ptr<AstrumTextureMesh> mesh = nullptr;
};