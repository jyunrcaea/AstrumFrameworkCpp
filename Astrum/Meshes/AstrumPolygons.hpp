#pragma once
#include "AstrumMesh.hpp"
#include "../Units/AstrumVertexColor.hpp"

namespace Astrum
{
	// 색이 있는 다각형을 구성하기 위한 매시.
	class Polygons : public Mesh<VertexColor> {
	public:
		Polygons(
			const std::vector<VertexColor>& vertices,
			const std::vector<unsigned short>& indices,
			D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
			D3D11_USAGE vertexUsage = D3D11_USAGE_DYNAMIC,
			D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
		) : Mesh<VertexColor>(vertices, indices, primitive, format, vertexUsage, indexUsage) { }
		Polygons(const MeshDescription<VertexColor>& desc) : Mesh<VertexColor>(desc) { };

	public:
		static inline std::shared_ptr<Polygons> MakeShared(
			const std::vector<VertexColor>& vertices,
			const std::vector<unsigned short>& indices,
			D3D11_PRIMITIVE_TOPOLOGY primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			DXGI_FORMAT format = DXGI_FORMAT_R16_UINT,
			D3D11_USAGE vertexUsage = D3D11_USAGE_DYNAMIC,
			D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT
		) {
			return std::make_shared<Polygons>(vertices, indices, primitive, format, vertexUsage, indexUsage);
		}
	};
}