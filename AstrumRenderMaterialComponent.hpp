#pragma once
#include "AstrumRenderComponent.hpp"
#include "AstrumTextureMesh.hpp"
#include "AstrumMaterial.hpp"
#include "AstrumTextureVertex.hpp"

class AstrumRenderMaterialComponent : public AstrumRenderComponent
{
public:
    std::shared_ptr<class AstrumMaterial> Material = nullptr;
    std::shared_ptr<struct AstrumTextureMesh> Mesh = nullptr;
    virtual std::shared_ptr<struct IAstrumShaderSetup> GetDefaultShaderPipeline() const override;

    //너비와 높이를 입력받고, 직사각형 매시를 생성하고 할당합니다.
    void SetupRectangleMesh(float width, float height, float z = 0.f);
    //머터리얼이 참조하는 텍스쳐의 크기대로 매시를 생성합니다.
    void SetupMeshFromTexture(float z = 0.f);

protected:
    virtual void PreRender() override;
    virtual void Render() override;
};