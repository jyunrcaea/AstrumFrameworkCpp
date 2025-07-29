#pragma once
#include "AstrumShapeObject.hpp"
#include "AstrumPolygons.hpp"

class AstrumTriangleObject : public AstrumShapeObject
{
public:
    AstrumTriangleObject();
    AstrumTriangleObject(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c);

    virtual void Draw() override;

    std::shared_ptr<AstrumPolygons> GetPolygons() const;
    void SetPolygons(const AstrumVertexColor& a, const AstrumVertexColor& b, const AstrumVertexColor& c);
};