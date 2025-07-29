#include "AstrumTriangleObject.hpp"
#include "AstrumRenderer.hpp"

AstrumTriangleObject::AstrumTriangleObject() {}
AstrumTriangleObject::AstrumTriangleObject(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c)
{
	SetPolygons(a, b, c);
}

void AstrumTriangleObject::Draw()
{
	if (Visible) {
		AstrumRenderer::Instance().EnqueueRenderable(renderPolygonsComponent);
	}
}

std::shared_ptr<AstrumPolygons> AstrumTriangleObject::GetPolygons() const {
	return renderPolygonsComponent->Polygons;
}

void AstrumTriangleObject::SetPolygons(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c) {
	renderPolygonsComponent->Polygons = AstrumPolygons::MakeShared({ a, b, c }, { 0, 1, 2 });
}