#include "AstrumCircleObject.hpp"

AstrumCircleObject::AstrumCircleObject(const AstrumVertexColor& center, float radius, const unsigned short segment) {
    std::vector<AstrumVertexColor> vertices;
    vertices.push_back(center);

    for (int i = 0; i <= segment; ++i) {
        float angle = 2.0f * 3.14159265358979323846f * static_cast<float>(i) / static_cast<float>(segment);
        float x = center.Position.X + radius * std::cos(angle);
        float y = center.Position.Y + radius * std::sin(angle);
        vertices.push_back({ {x, y, center.Position.Z}, center.Color });
    }

    std::vector<uint16_t> indices;
    for (int i = 0; i < segment; ++i) {
        indices.push_back(0);
        indices.push_back(static_cast<uint16_t>(i + 2));
        indices.push_back(static_cast<uint16_t>(i + 1));
    }

    circlePolygon = std::make_unique<AstrumPolygons>(vertices, indices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT);
}

AstrumCircleObject::AstrumCircleObject(const AstrumVertexColor& center, float radius, const std::vector<AstrumColor>& colors, const unsigned short segment)
{
    std::vector<AstrumVertexColor> vertices;
    vertices.push_back(center);

    const float sector = (float)segment / colors.size();
    for (int i = 0; i <= segment; ++i) {
        float angle = 2.0f * 3.14159265358979323846f * static_cast<float>(i) / static_cast<float>(segment);
        float x = center.Position.X + radius * std::cos(angle);
        float y = center.Position.Y + radius * std::sin(angle);
        vertices.push_back({ {x, y, center.Position.Z}, colors[(int)(i / sector) % colors.size()]});
    }

    std::vector<uint16_t> indices;
    for (int i = 0; i < segment; ++i) {
        indices.push_back(0);
        indices.push_back(static_cast<uint16_t>(i + 2));
        indices.push_back(static_cast<uint16_t>(i + 1));
    }

    circlePolygon = std::make_unique<AstrumPolygons>(vertices, indices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT);
}

void AstrumCircleObject::Render() {
    AstrumDrawableObject::Render();
    if (circlePolygon) {
        circlePolygon->Render();
    }
}