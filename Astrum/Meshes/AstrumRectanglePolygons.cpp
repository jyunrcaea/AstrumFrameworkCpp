#include "AstrumRectanglePolygons.hpp"

namespace Astrum
{
	namespace {
		inline std::vector<VertexColor> Colors2VertexColor(float width, float height, const Color& color) {
			width /= 2;
			height /= 2;
			std::vector<VertexColor> dots = {
				{ { -width, height }, color },
				{ { width, height }, color },
				{ { -width, -height }, color },
				{ { width, -height }, color }
			};
			return dots;
		}
		inline std::vector<VertexColor> Color2VertexColor(float width, float height, const Color& color) {
			width /= 2;
			height /= 2;
			std::vector<VertexColor> dots = {
				{ { -width, height }, color },
				{ { width, height }, color },
				{ { -width, -height }, color },
				{ { width, -height }, color }
			};
			return dots;
		}
	}

	RectanglePolygons::RectanglePolygons(float width, float height, const Color& color)
		: Polygons(Color2VertexColor(width, height, color), { 0, 1, 2, 1, 3, 2 }) {}

	RectanglePolygons::RectanglePolygons(const VertexColor& leftTop, const VertexColor& rightTop, const VertexColor& leftBottom, const VertexColor& rightBottom)
		: Polygons({ leftTop, rightTop, leftBottom, rightBottom }, { 0, 1, 2, 1, 3, 2 }) {}

	void RectanglePolygons::SetColor(const Color& color) {
		SetColor(color, color, color, color);
	}
	void RectanglePolygons::SetColor(const Color& leftTop, const Color& rightTop, const Color& leftBottom, const Color& rightBottom) {
		vertices[0].Color = leftTop;
		vertices[1].Color = rightTop;
		vertices[2].Color = leftBottom;
		vertices[3].Color = rightBottom;
		UpdateVertexBuffer();
	}

	Color RectanglePolygons::GetLeftTopColor() const { return static_cast<Color>(vertices[0].Color); }
	Color RectanglePolygons::GetRightTopColor() const { return static_cast<Color>(vertices[1].Color); }
	Color RectanglePolygons::GetLeftBottomColor() const { return static_cast<Color>(vertices[2].Color); }
	Color RectanglePolygons::GetRightBottomColor() const { return static_cast<Color>(vertices[3].Color); }
}
