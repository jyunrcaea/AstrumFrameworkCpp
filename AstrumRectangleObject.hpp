#pragma once
#include "AstrumDrawableObject.hpp"
#include "AstrumPolygons.hpp"

class AstrumRectangleObject : public AstrumDrawableObject {
public:
    AstrumRectangleObject()
        : AstrumRectangleObject({}, {}, {}, {}) {
    }

    AstrumRectangleObject(const AstrumVertexColor& lt, const AstrumVertexColor& rt,
        const AstrumVertexColor& lb, const AstrumVertexColor& rb) : AstrumDrawableObject()
    {
        std::vector<AstrumVertexColor> vertices = { lt, rt, lb, rb };
        std::vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
        rectanglePolygon = std::make_unique<AstrumPolygons>(
            vertices, indices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT);
    }

protected:
    void Render() override {
        if (rectanglePolygon)
            rectanglePolygon->Render();
    }

private:
    std::unique_ptr<AstrumPolygons> rectanglePolygon;
};
