#include "AstrumTriangleObject.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

namespace Astrum
{
	TriangleObject::TriangleObject() {}
	TriangleObject::TriangleObject(const VertexColor& a, const VertexColor& b, const VertexColor& c)
	{
		SetPolygons(a, b, c);
	}

	std::shared_ptr<Polygons> TriangleObject::GetPolygons() const {
		return renderPolygonsComponent->Polygons;
	}

	void TriangleObject::SetPolygons(const VertexColor& a, const VertexColor& b, const VertexColor& c) {
		renderPolygonsComponent->Polygons = Polygons::MakeShared({ a, b, c }, { 0, 1, 2 });
	}
}