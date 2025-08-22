#pragma once
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumPolygons.hpp"

namespace Astrum
{
	class TriangleObject : public ShapeObject
	{
	public:
		TriangleObject();
		TriangleObject(const VertexColor& a, const VertexColor& b, const VertexColor& c);

		std::shared_ptr<Polygons> GetPolygons() const;
		void SetPolygons(const VertexColor& a, const VertexColor& b, const VertexColor& c);
	};
}