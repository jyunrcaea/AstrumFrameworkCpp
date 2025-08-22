#include "AstrumCirclePolygons.hpp"
#include <numbers>

namespace Astrum
{
	namespace {
		using ushort = unsigned short;

		std::vector<VertexColor> CreateCircleVertices(const VertexColor& center, float radius, const unsigned short segment) {
			std::vector<VertexColor> vertices;
			vertices.push_back(center);

			for (int i = 0; i <= segment; ++i) {
				const float angle = static_cast<float>(2.0 * std::numbers::pi * i / segment);
				vertices.emplace_back(Vector3{
					center.Position.X + radius * std::cos(angle),
					center.Position.Y + radius * std::sin(angle),
					center.Position.Z
					}, center.Color);
			}

			return vertices;
		}

		std::vector<VertexColor> CreateCircleVertices(const VertexColor& center, float radius, const std::vector<Color>& colors, const unsigned short segment) {
			std::vector<VertexColor> vertices;
			vertices.push_back(center);

			const float sector = (float)segment / colors.size();
			for (int i = 0; i <= segment; ++i) {
				const float angle = static_cast<float>(2.0 * std::numbers::pi * i / segment);
				vertices.emplace_back(Vector3{
					center.Position.X + radius * std::cos(angle),
					center.Position.Y + radius * std::sin(angle),
					center.Position.Z
					}, colors[static_cast<int>(i / sector) % colors.size()]);
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

	CirclePolygons::CirclePolygons(const VertexColor& center, float radius, const unsigned short segment)
		: Polygons(CreateCircleVertices(center, radius, segment), CreateCircleIndices(segment)) {}

	CirclePolygons::CirclePolygons(const VertexColor& center, float radius, const std::vector<Color>& colors, const unsigned short segment)
		: Polygons(CreateCircleVertices(center, radius, colors, segment), CreateCircleIndices(segment)) {}
}