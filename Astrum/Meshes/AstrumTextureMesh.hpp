#pragma once
#include "AstrumMesh.hpp"
#include "../Units/AstrumTextureVertex.hpp"
#include "../Vectors/AstrumVector3.hpp"

class AstrumTextureMesh : public AstrumMesh<AstrumTextureVertex>
{
public:
    AstrumTextureMesh(
        const std::vector<AstrumTextureVertex>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    );
    AstrumTextureMesh(const AstrumVector3& leftTop, const AstrumVector3& rightTop, const AstrumVector3& leftBottom, const AstrumVector3& rightBottom);

public:
    static inline std::shared_ptr<AstrumTextureMesh> MakeShared(
        const std::vector<AstrumTextureVertex>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    ) {
        return std::make_shared<AstrumTextureMesh>(vertices, indices, primitive, format, vertexUsage, indexUsage);
    }
    static inline std::shared_ptr<AstrumTextureMesh> MakeShared(
        const AstrumVector3& leftTop, const AstrumVector3& rightTop, const AstrumVector3& leftBottom, const AstrumVector3& rightBottom
    ) {
        return std::make_shared<AstrumTextureMesh>(leftTop, rightTop, leftBottom, rightBottom);
    }
};