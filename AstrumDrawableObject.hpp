#pragma once
#include "AstrumObject.hpp"
#include "IAstrumRenderable.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumTransformConstantBuffer.hpp"
#include <DirectXMath.h>
#include <memory>

class AstrumDrawableObject : public AstrumObject, public IAstrumRenderable, public std::enable_shared_from_this<AstrumDrawableObject> {
public:
    void Draw() override {
        AstrumRenderer::Instance().EnqueueRenderable(shared_from_this());
    }
    void Render() override {}

protected:
    void Rendering() override {
        AstrumMatrix scaleMat, rotMat, transMat;

        scaleMat.Scaling(scale);
        rotMat.Rotation(rotation);
        transMat.Translation(position);

        transformBuffer.World = scaleMat * rotMat * transMat;

        transformBuffer.Projection = DirectX::XMMatrixPerspectiveFovLH(
            DirectX::XM_PIDIV2, 1280.0f / 720.0f, 0.5f, 1000.0f);

        transformBuffer.UpdateBuffer();

        Render();
    }
    AstrumTransformConstantBuffer transformBuffer;
};
