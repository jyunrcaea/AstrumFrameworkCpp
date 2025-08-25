#pragma once
#include <span>
#include <cstddef>
#include "AstrumConstantBuffer.hpp"
#include "../Data/AstrumTransformData.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

class AstrumTransformConstantBuffer : public AstrumConstantBuffer {
public:
    AstrumTransformConstantBuffer();

    AstrumMatrix& World = data.World;
    AstrumMatrix& View = data.View;
    AstrumMatrix& Projection = data.Projection;
    AstrumMatrix& WorldView = data.WorldView;
    AstrumMatrix& WorldViewProjection = data.WorldViewProjection;

    virtual void UpdateBuffer() override;

private:
    AstrumTransformData data{};
};