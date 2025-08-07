#include "AstrumPolygonsObject.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumPolygonsObject::AstrumPolygonsObject()
{
	AddComponent(renderPolygonsComponent);
}

AstrumPolygonsObject::AstrumPolygonsObject(const std::shared_ptr<AstrumPolygons>& polygons) : AstrumPolygonsObject()
{
	renderPolygonsComponent->Polygons = polygons;
}

void AstrumPolygonsObject::Draw() {
	if (Visible && renderPolygonsComponent) {
		AstrumRenderer::Instance().EnqueueRenderable(renderPolygonsComponent);
	}
}

std::shared_ptr<AstrumPolygons>& AstrumPolygonsObject::GetPolygons() {
	return renderPolygonsComponent->Polygons;
}

void AstrumPolygonsObject::SetPolygons(const std::shared_ptr<AstrumPolygons>& polygons) {
	renderPolygonsComponent->Polygons = polygons;
}