#pragma once
#include "AstrumComponent.hpp"
#include "../Buffers/AstrumTransformConstantBuffer.hpp"
#include "../Graphics/IAstrumRenderable.hpp"

// 렌더링을 수행하는 기본 컴포넌트입니다.
class AstrumRenderComponent : public AstrumComponent, public IAstrumRenderable {
public:
    virtual std::shared_ptr<struct IAstrumShaderSetup> GetDefaultShaderPipeline() const = 0;
    std::shared_ptr<struct IAstrumShaderSetup> CustomShaderPipeline = nullptr;

    virtual void Draw() override;
protected:
    // 셰이더를 설정합니다.
    virtual void Render() override;
    // 렌더링전 컴포넌트 소유자(IAstrumObject)의 transform를 가져와 상수 버퍼에 넣게 될 행렬을 계산합니다.
    virtual void PreRender() override;

private:
    AstrumTransformConstantBuffer transformBuffer;
};