#include "AstrumRectangleObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

namespace Astrum
{
	RectangleObject::RectangleObject() {}
	RectangleObject::RectangleObject(const std::shared_ptr<RectanglePolygons>& rectanglePolygon) {
		SetRectanglePolygons(rectanglePolygon);
	}
	RectangleObject::RectangleObject(float width, float height, const Color& color) {
		SetRectanglePolygons(RectanglePolygons::MakeShared(width, height, color));
	}

	std::shared_ptr<RectanglePolygons> RectangleObject::GetRectanglePolygons() const {
		return rectanglePolygon;
	}

	void RectangleObject::SetRectanglePolygons(const std::shared_ptr<RectanglePolygons>& newRectanglePolygon) {
		renderPolygonsComponent->Polygons = (this->rectanglePolygon = newRectanglePolygon);
	}

	void RectangleObject::SetColor(const Color& color) {
		rectanglePolygon->SetColor(color);
	}
	void RectangleObject::SetColor(const Color& leftTop, const Color& rightTop, const Color& leftBottom, const Color& rightBottom) {
		rectanglePolygon->SetColor(leftTop, rightTop, leftBottom, rightBottom);
	}
}