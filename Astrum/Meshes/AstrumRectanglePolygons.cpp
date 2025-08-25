#include "AstrumRectanglePolygons.hpp"

namespace {
    inline std::vector<AstrumVertexColor> Colors2VertexColor(float width, float height, const AstrumColor& color) {
        width /= 2;
        height /= 2;
        std::vector<AstrumVertexColor> dots = {
            { { -width, height }, color },
            { { width, height }, color },
            { { -width, -height }, color },
            { { width, -height }, color }
        };
        return dots;
    }
    inline std::vector<AstrumVertexColor> Color2VertexColor(float width, float height, const AstrumColor& color) {
        width /= 2;
        height /= 2;
        std::vector<AstrumVertexColor> dots = {
            { { -width, height }, color },
            { { width, height }, color },
            { { -width, -height }, color },
            { { width, -height }, color }
        };
        return dots;
    }
}

AstrumRectanglePolygons::AstrumRectanglePolygons(float width, float height, const AstrumColor& color) 
    : AstrumPolygons(Color2VertexColor(width, height, color), { 0, 1, 2, 1, 3, 2 }) {}

AstrumRectanglePolygons::AstrumRectanglePolygons(const AstrumVertexColor& leftTop, const AstrumVertexColor& rightTop, const AstrumVertexColor& leftBottom, const AstrumVertexColor& rightBottom)
    : AstrumPolygons({ leftTop, rightTop, leftBottom, rightBottom }, { 0, 1, 2, 1, 3, 2 }) {}

void AstrumRectanglePolygons::SetColor(const AstrumColor& color) {
    SetColor(color, color, color, color);
}
void AstrumRectanglePolygons::SetColor(const AstrumColor& leftTop, const AstrumColor& rightTop, const AstrumColor& leftBottom, const AstrumColor& rightBottom) {
    vertices[0].Color = leftTop;
    vertices[1].Color = rightTop;
    vertices[2].Color = leftBottom;
    vertices[3].Color = rightBottom;
    UpdateVertexBuffer();
}

AstrumColor AstrumRectanglePolygons::GetLeftTopColor() const { return static_cast<AstrumColor>(vertices[0].Color); }
AstrumColor AstrumRectanglePolygons::GetRightTopColor() const { return static_cast<AstrumColor>(vertices[1].Color); }
AstrumColor AstrumRectanglePolygons::GetLeftBottomColor() const { return static_cast<AstrumColor>(vertices[2].Color); }
AstrumColor AstrumRectanglePolygons::GetRightBottomColor() const { return static_cast<AstrumColor>(vertices[3].Color); }
