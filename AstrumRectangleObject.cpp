#include <vector>
#include <memory>
#include "AstrumRectangleObject.hpp"
#include "AstrumPolygons.hpp"

AstrumRectangleObject::AstrumRectangleObject() : AstrumRectangleObject({}, {}, {}, {}) { }

namespace {
    inline std::vector<AstrumVertexColor> Color2VertexColor(float width, float height, const AstrumColor& leftTop, const AstrumColor& rightTop, const AstrumColor& leftBottom, const AstrumColor& rightBottom) {
        width /= 2;
        height /= 2;
        std::vector<AstrumVertexColor> dots = {
            { { -width, height}, leftTop },
            { { width, height}, rightTop },
            { { -width, -height}, leftBottom },
            { { width, -height}, rightBottom }
        };
        return dots;
	}
}

AstrumRectangleObject::AstrumRectangleObject(const AstrumColor& leftTop, const AstrumColor& rightTop, const AstrumColor& leftBottom, const AstrumColor& rightBottom, float width, float height)
    : rectanglePolygon(
        Color2VertexColor(width, height, leftTop, rightTop, leftBottom, rightBottom),
        {0, 1, 2, 1, 3, 2}, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT
    )
{ }

void AstrumRectangleObject::Render()
{
    AstrumDrawableObject::Render();

    rectanglePolygon.Render();
}
