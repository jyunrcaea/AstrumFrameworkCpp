#include "AstrumPolygons.hpp"

AstrumPolygons::AstrumPolygons(const std::vector<AstrumVertexColor>& vertices,
    const std::vector<uint16_t>& indices,
    D3D11_PRIMITIVE_TOPOLOGY primitive,
    DXGI_FORMAT format,
    D3D11_USAGE vertexUsage,
    D3D11_USAGE indexUsage)
    : primitive(primitive)
    , indexBufferFormat(format)
    , indexCount(static_cast<UINT>(indices.size()))
{
    if (!AstrumRenderer::Instance().CreateBuffer(
        vertices, vertexBuffer, D3D11_BIND_VERTEX_BUFFER, vertexUsage))
    {
        throw AstrumException("Create vertex buffer failed.");
    }

    if (!AstrumRenderer::Instance().CreateBuffer(
        indices, indexBuffer, D3D11_BIND_INDEX_BUFFER, indexUsage))
    {
        throw AstrumException("Create index buffer failed.");
    }
}

AstrumPolygons::~AstrumPolygons() {
    Dispose();
}

void AstrumPolygons::Render() {
    UINT stride = sizeof(AstrumVertexColor);
    UINT offset = 0;
    auto* ctx = AstrumRenderer::Instance().GetContext();

    ctx->IASetPrimitiveTopology(primitive);
    ctx->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    ctx->IASetIndexBuffer(indexBuffer.Get(), indexBufferFormat, 0);
    ctx->DrawIndexed(indexCount, 0, 0);
}

void AstrumPolygons::Dispose() {
    vertexBuffer.Reset();
    indexBuffer.Reset();
}