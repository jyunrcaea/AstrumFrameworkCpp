#include "AstrumPolygonsObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

AstrumPolygonsObject::AstrumPolygonsObject()
{
	AddComponent(renderPolygonsComponent);
}

AstrumPolygonsObject::AstrumPolygonsObject(const std::shared_ptr<AstrumPolygons>& polygons) : AstrumPolygonsObject()
{
	renderPolygonsComponent->Polygons = polygons;
}

std::shared_ptr<AstrumPolygons>& AstrumPolygonsObject::GetPolygons() {
	return renderPolygonsComponent->Polygons;
}

void AstrumPolygonsObject::SetPolygons(const std::shared_ptr<AstrumPolygons>& polygons) {
	renderPolygonsComponent->Polygons = polygons;
}