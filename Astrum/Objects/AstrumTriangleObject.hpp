#pragma once
#include <memory>
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumPolygons.hpp"

class AstrumTriangleObject : public AstrumShapeObject
{
public:
    AstrumTriangleObject();
    AstrumTriangleObject(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c);

    std::shared_ptr<AstrumPolygons> GetPolygons() const;
    void SetPolygons(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c);

public:
    static std::shared_ptr<AstrumTriangleObject> MakeShared() { return std::make_shared<AstrumTriangleObject>(); }
    static std::shared_ptr<AstrumTriangleObject> MakeShared(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c) {
        return std::make_shared<AstrumTriangleObject>(a, b, c);
	}
};