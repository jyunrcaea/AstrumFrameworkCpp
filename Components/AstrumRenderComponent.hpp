#pragma once
#include "AstrumComponent.hpp"
#include "../Buffers/AstrumTransformConstantBuffer.hpp"
#include "../Graphics/IAstrumRenderable.hpp"

class AstrumRenderComponent : public AstrumComponent, public IAstrumRenderable {
public:
    virtual std::shared_ptr<struct IAstrumShaderSetup> GetDefaultShaderPipeline() const = 0;
    std::shared_ptr<struct IAstrumShaderSetup> CustomShaderPipeline = nullptr;

protected:
    // 셰이더를 설정합니다.
    virtual void Render() override;
    // 렌더링전 컴포넌트 소유자(IAstrumObject)의 transform를 가져와 상수 버퍼에 넣게 될 행렬을 계산합니다.
    virtual void PreRender() override;

private:
    AstrumTransformConstantBuffer transformBuffer;
};