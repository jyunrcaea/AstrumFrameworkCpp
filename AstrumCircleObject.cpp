#include "AstrumCircleObject.hpp"

const int CIRCLE_SEGMENTS = 128;

AstrumCircleObject::AstrumCircleObject(const AstrumVertexColor& center, float radius) {
    std::vector<AstrumVertexColor> vertices;
    vertices.push_back(center);

    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i) {
        float angle = 2.0f * 3.14159265358979323846f * static_cast<float>(i) / static_cast<float>(CIRCLE_SEGMENTS);
        float x = center.Position.X + radius * std::cos(angle);
        float y = center.Position.Y + radius * std::sin(angle);
        vertices.push_back({ {x, y, center.Position.Z}, center.Color });
    }

    std::vector<uint16_t> indices;
    for (int i = 0; i < CIRCLE_SEGMENTS; ++i) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    circlePolygon = std::make_unique<AstrumPolygons>(vertices, indices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT);
}

void AstrumCircleObject::Render() {
    AstrumDrawableObject::Render();
    if (circlePolygon) {
        circlePolygon->Render();
    }
}