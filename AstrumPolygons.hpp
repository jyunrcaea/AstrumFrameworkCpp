#pragma once
#include "AstrumMesh.hpp"
#include "AstrumVertexColor.hpp"

class AstrumPolygons : public AstrumMesh<AstrumVertexColor> {
public:
    AstrumPolygons(
        const std::vector<AstrumVertexColor>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    ) : AstrumMesh<AstrumVertexColor>(AstrumMeshDescription<AstrumVertexColor>{ vertices, indices, primitive, format, vertexUsage, indexUsage }) { }
    AstrumPolygons(const AstrumMeshDescription<AstrumVertexColor>& desc) : AstrumMesh<AstrumVertexColor>(desc) { };

public:
    static inline std::shared_ptr<AstrumPolygons> MakeShared(
        const std::vector<AstrumVertexColor>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    ) {
        return std::make_shared<AstrumPolygons>(vertices, indices, primitive, format, vertexUsage, indexUsage);
    }
    static inline std::shared_ptr<AstrumPolygons> MakeSharedByRectangle(
        const AstrumVertexColor& leftTop,
        const AstrumVertexColor& rightTop,
        const AstrumVertexColor& leftBottom,
        const AstrumVertexColor& rightBottom
    ) {
        return MakeShared(
            { leftTop, rightTop, leftBottom, rightBottom },
            { 3, 2, 1, 1, 2, 0}
        );
    }
    static inline std::shared_ptr<AstrumPolygons> MakeSharedByRectangle(
        const AstrumVector3& leftTop,
        const AstrumVector3& rightTop,
        const AstrumVector3& leftBottom,
        const AstrumVector3& rightBottom,
        const AstrumColor& color
    ) {
        return MakeSharedByRectangle(
            AstrumVertexColor{ leftTop, color },
            AstrumVertexColor{ rightTop, color },
            AstrumVertexColor{ leftBottom, color },
            AstrumVertexColor{ rightBottom, color}
        );
    }
};