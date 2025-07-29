#include "AstrumCirclePolygons.hpp"
#include <numbers>

namespace {
    using ushort = unsigned short;

    std::vector<AstrumVertexColor> CreateCircleVertices(const AstrumVertexColor& center, float radius, const unsigned short segment) {
        std::vector<AstrumVertexColor> vertices;
        vertices.push_back(center);

        for (int i = 0; i <= segment; ++i) {
            float angle = 2.0f * 3.14159265358979323846f * static_cast<float>(i) / static_cast<float>(segment);
            float x = center.Position.X + radius * std::cos(angle);
            float y = center.Position.Y + radius * std::sin(angle);
            vertices.push_back({ { x, y, center.Position.Z }, center.Color });
        }

        return vertices;
    }

    std::vector<AstrumVertexColor> CreateCircleVertices(const AstrumVertexColor& center, float radius, const std::vector<AstrumColor>& colors, const unsigned short segment) {
        std::vector<AstrumVertexColor> vertices;
        vertices.push_back(center);

        const float sector = (float)segment / colors.size();
        for (int i = 0; i <= segment; ++i) {
            float angle = static_cast<float>(2.0 * std::numbers::pi * i / segment);
            float x = center.Position.X + radius * std::cos(angle);
            float y = center.Position.Y + radius * std::sin(angle);
            vertices.push_back({ { x, y, center.Position.Z }, colors[(int)(i / sector) % colors.size()] });
        }

        return vertices;
    }

    std::vector<ushort> CreateCircleIndices(const unsigned short segment) {
        std::vector<ushort> indices;
        for (int i = 0; i < segment; ++i) {
            indices.push_back(0);
            indices.push_back(static_cast<ushort>(i + 2));
            indices.push_back(static_cast<ushort>(i + 1));
        }

        return indices;
    }
}

AstrumCirclePolygons::AstrumCirclePolygons(const AstrumVertexColor& center, float radius, const unsigned short segment)
    : AstrumPolygons(CreateCircleVertices(center, radius, segment), CreateCircleIndices(segment)) {}

AstrumCirclePolygons::AstrumCirclePolygons(const AstrumVertexColor& center, float radius, const std::vector<AstrumColor>& colors, const unsigned short segment)
    : AstrumPolygons(CreateCircleVertices(center, radius, colors, segment), CreateCircleIndices(segment)) {}