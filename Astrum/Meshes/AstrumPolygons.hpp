#pragma once
#include "AstrumMesh.hpp"
#include "../Units/AstrumVertexColor.hpp"

// 색이 있는 다각형을 구성하기 위한 매시.
class AstrumPolygons : public AstrumMesh<AstrumVertexColor> {
public:
    AstrumPolygons(
        const std::vector<AstrumVertexColor>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DYNAMIC,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    ) : AstrumMesh<AstrumVertexColor>(vertices, indices, primitive, format, vertexUsage, indexUsage) { }
    AstrumPolygons(const AstrumMeshDescription<AstrumVertexColor>& desc) : AstrumMesh<AstrumVertexColor>(desc) { };
    
public:
    static inline std::shared_ptr<AstrumPolygons> MakeShared(
        const std::vector<AstrumVertexColor>& vertices,
        const std::vector<unsigned short>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DYNAMIC,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
    ) {
        return std::make_shared<AstrumPolygons>(vertices, indices, primitive, format, vertexUsage, indexUsage);
    }
};