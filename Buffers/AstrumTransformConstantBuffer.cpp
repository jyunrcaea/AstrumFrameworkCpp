#include "AstrumTransformConstantBuffer.hpp"

AstrumTransformConstantBuffer::AstrumTransformConstantBuffer()
    : AstrumConstantBuffer(sizeof(AstrumTransformData)) {
#if _DEBUG
    if (GetBufferSize() % 16 != 0)
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

    //Update(std::as_bytes(std::span{ &data, 1 }));
    UpdateConstantBuffer(data);
    SetVertexShaderConstantBuffer(0);
#if _DEBUG
    if (nullptr == buffer) throw AstrumException("Buffer be nullptr.");
#endif
}