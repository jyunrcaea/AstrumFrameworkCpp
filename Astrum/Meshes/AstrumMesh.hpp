#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <span>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "../Graphics/IAstrumRenderable.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"
#include "../Units/AstrumVertexColor.hpp"

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
    );
    AstrumMesh(const AstrumMeshDescription<VertexType>& desc)
        : AstrumMesh(desc.vertices,desc.indices, desc.primitive, desc.format, desc.vertexUsage, desc.indexUsage) {}
    virtual void Render() override;

    D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() const { return primitive; }
    DXGI_FORMAT GetFormat() const { return bufferFormat; }

    operator bool() const { return vertexBuffer && indexBuffer; }
protected:
    virtual void PreRender() override {};

    std::vector<VertexType> vertices;
    void UpdateVertexBuffer() {
        std::span<const std::byte> data = std::as_bytes(std::span<AstrumVertexColor>{ vertices.data(), vertices.size()});
        auto* const ctx = AstrumRenderer::Instance().GetContext();

        D3D11_MAPPED_SUBRESOURCE mapped{};
        if (FAILED(ctx->Map(vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
#if _DEBUG
            throw AstrumException("Failed to map vertex buffer.");
#endif
        }

        std::memcpy(mapped.pData, data.data(), data.size());
        ctx->Unmap(vertexBuffer.Get(), 0);
    }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
    D3D11_PRIMITIVE_TOPOLOGY primitive;
    DXGI_FORMAT bufferFormat;
    unsigned int indexCount = 0;
	unsigned int vertexBufferOffset = 0;
};

template <typename VertexType>
AstrumMesh<VertexType>::AstrumMesh(const std::vector<VertexType>& vertices,
    const std::vector<unsigned short>& indices,
    D3D11_PRIMITIVE_TOPOLOGY primitive,
    DXGI_FORMAT format,
    D3D11_USAGE vertexUsage,
    D3D11_USAGE indexUsage)
 : vertices(vertices), primitive(primitive), bufferFormat(format), indexCount(static_cast<unsigned int>(indices.size())) {
    // Create vertex buffer
    if (false == AstrumRenderer::Instance().CreateBuffer(vertices, vertexBuffer, D3D11_BIND_VERTEX_BUFFER, vertexUsage)) {
#if _DEBUG
        throw AstrumException("Create vertex buffer failed.");
#else
        vertexBuffer.Reset();
        return;
#endif
    }
    // Create index buffer
    if (false == AstrumRenderer::Instance().CreateBuffer(indices, indexBuffer, D3D11_BIND_INDEX_BUFFER, indexUsage)) {
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
    unsigned int stride = sizeof(VertexType);

    auto* const ctx = AstrumRenderer::Instance().GetContext();

    ctx->IASetPrimitiveTopology(primitive);
    ctx->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &vertexBufferOffset);
    ctx->IASetIndexBuffer(indexBuffer.Get(), bufferFormat, 0);
    ctx->DrawIndexed(indexCount, 0, 0);
}