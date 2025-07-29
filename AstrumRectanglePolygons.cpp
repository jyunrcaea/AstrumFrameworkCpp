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
