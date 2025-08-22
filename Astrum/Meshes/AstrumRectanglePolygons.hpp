#pragma once
#include <memory>
#include "AstrumPolygons.hpp"

namespace Astrum
{
	class RectanglePolygons : public Polygons
	{
	public:
		RectanglePolygons(float width, float height, const Color& color);
		RectanglePolygons(const VertexColor& leftTop, const VertexColor& rightTop, const VertexColor& leftBottom, const VertexColor& rightBottom);

		void SetColor(const Color& color);
		void SetColor(const Color& leftTop, const Color& rightTop, const Color& leftBottom, const Color& rightBottom);

		Color GetLeftTopColor() const;
		Color GetRightTopColor() const;
		Color GetLeftBottomColor() const;
		Color GetRightBottomColor() const;

	public:
		static std::shared_ptr<RectanglePolygons> MakeShared(float width, float height, const Color& color) {
			return std::make_shared<RectanglePolygons>(width, height, color);
		}
		static std::shared_ptr<RectanglePolygons> MakeShared(const VertexColor& leftTop, const VertexColor& rightTop, const VertexColor& leftBottom, const VertexColor& rightBottom) {
			return std::make_shared<RectanglePolygons>(leftTop, rightTop, leftBottom, rightBottom);
		}
	};
}