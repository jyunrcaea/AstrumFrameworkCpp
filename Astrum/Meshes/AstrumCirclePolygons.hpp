#pragma once
#include "AstrumPolygons.hpp"
#include "../Units/AstrumVertexColor.hpp"

namespace Astrum
{
	class CirclePolygons : public Polygons
	{
	public:
		CirclePolygons(const VertexColor& center, float radius, const unsigned short segment = 128);
		CirclePolygons(const VertexColor& center, float radius, const std::vector<Color>& colors, const unsigned short segment = 128);

	public:
		static std::shared_ptr<CirclePolygons> MakeShared(const VertexColor& center, float radius, const unsigned short segment = 128) {
			return std::make_shared<CirclePolygons>(center, radius, segment);
		}
		static std::shared_ptr<CirclePolygons> MakeShared(const VertexColor& center, float radius, const std::vector<Color>& colors, const unsigned short segment = 128) {
			return std::make_shared<CirclePolygons>(center, radius, colors, segment);
		}
	};
}
