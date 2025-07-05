#include "AstrumTransformConstantBuffer.hpp"

AstrumTransformConstantBuffer::AstrumTransformConstantBuffer() : AstrumConstantBuffer(sizeof(AstrumTransformData))
{
#if _DEBUG
    if (size % 16 != 0)
        throw AstrumException("Constant buffer size must be 16-byte aligned.");
#endif
    data.View = AstrumMatrix::Identity;
}

void AstrumTransformConstantBuffer::UpdateBuffer() {
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
