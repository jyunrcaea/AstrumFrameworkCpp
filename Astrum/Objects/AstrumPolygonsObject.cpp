#include "AstrumPolygonsObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

namespace Astrum
{
	PolygonsObject::PolygonsObject()
	{
		AddComponent(renderPolygonsComponent);
	}

	PolygonsObject::PolygonsObject(const std::shared_ptr<Polygons>& polygons) : PolygonsObject()
	{
		renderPolygonsComponent->Polygons = polygons;
	}

	std::shared_ptr<Polygons>& PolygonsObject::GetPolygons() {
		return renderPolygonsComponent->Polygons;
	}

	void PolygonsObject::SetPolygons(const std::shared_ptr<Polygons>& polygons) {
		renderPolygonsComponent->Polygons = polygons;
	}
}