#include "AstrumCircleObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

namespace Astrum
{
	CircleObject::CircleObject() {}
	CircleObject::CircleObject(const std::shared_ptr<CirclePolygons>& circlePolygon) {
		SetCirclePolygons(circlePolygon);
	}
	CircleObject::CircleObject(const VertexColor& center, float radius, const unsigned short segment) {
		SetCirclePolygons(CirclePolygons::MakeShared(center, radius, segment));
	}

	std::shared_ptr<CirclePolygons> CircleObject::GetCirclePolygons() const { return circlePolygon; }

	void CircleObject::SetCirclePolygons(const std::shared_ptr<CirclePolygons>& newCirclePolygon) {
		renderPolygonsComponent->Polygons = (this->circlePolygon = newCirclePolygon);
	}
}