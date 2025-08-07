#include "AstrumCircleObject.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumCircleObject::AstrumCircleObject() {}
AstrumCircleObject::AstrumCircleObject(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon) {
	SetCirclePolygons(circlePolygon);
}
AstrumCircleObject::AstrumCircleObject(const AstrumVertexColor& center, float radius, const unsigned short segment) {
	SetCirclePolygons(AstrumCirclePolygons::MakeShared(center, radius, segment));
}

void AstrumCircleObject::Draw() {
	if (Visible && circlePolygon) {
		AstrumRenderer::Instance().EnqueueRenderable(renderPolygonsComponent);
	}
}

std::shared_ptr<AstrumCirclePolygons> AstrumCircleObject::GetCirclePolygons() const { return circlePolygon; }

void AstrumCircleObject::SetCirclePolygons(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon) {
	renderPolygonsComponent->Polygons = (this->circlePolygon = circlePolygon);
}