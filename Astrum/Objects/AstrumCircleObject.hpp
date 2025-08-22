#pragma once
#include <vector>
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumCirclePolygons.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

namespace Astrum
{
	class CircleObject : public ShapeObject {
	public:
		CircleObject();
		CircleObject(const std::shared_ptr<CirclePolygons>& circlePolygon);
		CircleObject(const VertexColor& center, float radius, const unsigned short segment = 128);

		std::shared_ptr<CirclePolygons> GetCirclePolygons() const;
		void SetCirclePolygons(const std::shared_ptr<CirclePolygons>& circlePolygon);

	private:
		std::shared_ptr<CirclePolygons> circlePolygon;
	};
}