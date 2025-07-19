#include "AstrumTriangleObject.hpp"

AstrumTriangleObject::AstrumTriangleObject() : AstrumTriangleObject({}, {}, {})
{
}

AstrumTriangleObject::AstrumTriangleObject(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c)
	: AstrumDrawableObject(), trianglePolygon({ a, b, c }, { 0, 1, 2 }, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT)
{
}

void AstrumTriangleObject::Render()
{
    trianglePolygon.Render();
}