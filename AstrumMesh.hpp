#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "IAstrumRenderable.hpp"
#include "AstrumVertexColor.hpp"
#include "AstrumException.hpp"
#include "AstrumRenderer.hpp"

template <typename VertexType>
struct AstrumMeshDescription {
    const std::vector<VertexType>& vertices;
    const std::vector<unsigned short>& indices;
    D3D11_PRIMITIVE_TOPOLOGY primitive;
    DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT;
    D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT;
};

template <typename VertexType>
class AstrumMesh : public IAstrumRenderable {
public:
    AstrumMesh(
        const std::vector<VertexType>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive,
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    ) : AstrumMesh(AstrumMeshDescription<VertexType>{ vertices, indices, primitive, format, vertexUsage, indexUsage }) { }
    AstrumMesh(const AstrumMeshDescription<VertexType>& desc);
    virtual void Render() override;

    D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() const { return primitive; }
    DXGI_FORMAT GetFormat() const { return bufferFormat; }

    operator bool() const { return vertexBuffer && indexBuffer; }
protected:
    virtual void PreRender() override {};

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
    D3D11_PRIMITIVE_TOPOLOGY primitive;
    DXGI_FORMAT bufferFormat;
    unsigned int indexCount = 0;
};

template <typename VertexType>
AstrumMesh<VertexType>::AstrumMesh(const AstrumMeshDescription<VertexType>& desc)
 : primitive(desc.primitive), bufferFormat(desc.format), indexCount(static_cast<unsigned int>(desc.indices.size())) {
    // Create vertex buffer
    if (false == AstrumRenderer::Instance().CreateBuffer(desc.vertices, vertexBuffer, D3D11_BIND_VERTEX_BUFFER, desc.vertexUsage)) {
#if _DEBUG
        throw AstrumException("Create vertex buffer failed.");
#else
        vertexBuffer.Reset();
        return;
#endif
    }
    // Create index buffer
    if (false == AstrumRenderer::Instance().CreateBuffer(desc.indices, indexBuffer, D3D11_BIND_INDEX_BUFFER, desc.indexUsage)) {
#if _DEBUG
        throw AstrumException("Create index buffer failed.");
#else
        vertexBuffer.Reset();
        indexBuffer.Reset();
        return;
#endif
    }
    // done.
}

template <typename VertexType>
void AstrumMesh<VertexType>::Render() {
    unsigned int stride = sizeof(VertexType), offset = 0;

    auto* ctx = AstrumRenderer::Instance().GetContext();

    ctx->IASetPrimitiveTopology(primitive);
    ctx->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    ctx->IASetIndexBuffer(indexBuffer.Get(), bufferFormat, 0);
    ctx->DrawIndexed(indexCount, 0, 0);
}