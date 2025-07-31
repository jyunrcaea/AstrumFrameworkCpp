#pragma once
#include "AstrumShapeObject.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

class AstrumPolygonsObject : public AstrumShapeObject
{
public:
	AstrumPolygonsObject();
	AstrumPolygonsObject(const std::shared_ptr<AstrumPolygons>& polygons);

	virtual void Draw() override;

	std::shared_ptr<AstrumPolygons>& GetPolygons();
	void SetPolygons(const std::shared_ptr<AstrumPolygons>& polygons);

private:
	std::shared_ptr<AstrumRenderPolygonsComponent> renderPolygonsComponent = std::make_shared<AstrumRenderPolygonsComponent>();
};