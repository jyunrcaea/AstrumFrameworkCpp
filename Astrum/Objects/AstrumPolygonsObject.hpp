#pragma once
#include "AstrumShapeObject.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

namespace Astrum
{
	class PolygonsObject : public ShapeObject
	{
	public:
		PolygonsObject();
		PolygonsObject(const std::shared_ptr<Polygons>& polygons);

		std::shared_ptr<Polygons>& GetPolygons();
		void SetPolygons(const std::shared_ptr<Polygons>& polygons);

	private:
		std::shared_ptr<RenderPolygonsComponent> renderPolygonsComponent = std::make_shared<RenderPolygonsComponent>();
	};
}