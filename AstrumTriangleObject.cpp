#include "AstrumTriangleObject.hpp"

AstrumTriangleObject::AstrumTriangleObject() : AstrumTriangleObject({}, {}, {})
{
}

AstrumTriangleObject::AstrumTriangleObject(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c)
{
    std::vector<AstrumVertexColor> vertices = { a, b, c };
    std::vector<uint16_t> indices = { 0, 1, 2 };
    trianglePolygon = std::make_unique<AstrumPolygons>(
        vertices, indices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT);
}

void AstrumTriangleObject::Render()
{
    AstrumDrawableObject::Render();
    if (trianglePolygon)
        trianglePolygon->Render();
}