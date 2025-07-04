#pragma once
#include "AstrumConstantBuffer.hpp"
#include "AstrumTransformData.hpp"
#include <span>

// AstrumMatrix::Identity must be defined as a static const member in AstrumMatrix.hpp

class AstrumTransformConstantBuffer : public AstrumConstantBuffer {
public:
    AstrumTransformConstantBuffer()
        : AstrumConstantBuffer(sizeof(AstrumTransformData))
    {
#if _DEBUG
        if (size % 16 != 0)
            throw AstrumException("Constant buffer size must be 16-byte aligned.");
#endif
        data.View = AstrumMatrix::Identity;
    }

    AstrumMatrix& World = data.World;
    AstrumMatrix& View = data.View;
    AstrumMatrix& Projection = data.Projection;
    AstrumMatrix& WorldView = data.WorldView;
    AstrumMatrix& WorldViewProjection = data.WorldViewProjection;

    void UpdateBuffer() {
        WorldView = World * View;
        WorldViewProjection = WorldView * Projection;

        World.Transpose();
        View.Transpose();
        Projection.Transpose();
        WorldView.Transpose();
        WorldViewProjection.Transpose();

        auto raw = std::as_bytes(std::span{ &data, 1 });
        Update(raw);

        AstrumRenderer::Instance().GetContext()->VSSetConstantBuffers(0, 1, buffer.GetAddressOf());
    }

private:
    AstrumTransformData data{};
};
