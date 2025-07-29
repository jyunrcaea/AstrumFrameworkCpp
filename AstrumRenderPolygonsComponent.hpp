#pragma once
#include <memory>
#include "AstrumPolygons.hpp"
#include "AstrumRenderComponent.hpp"

class AstrumRenderPolygonsComponent : public AstrumRenderComponent
{
public:
	std::shared_ptr<AstrumPolygons> Polygons = nullptr;

	virtual std::shared_ptr<struct IAstrumShaderSetup> GetDefaultShaderPipeline() const override;

protected:
	virtual void PreRender() override;
	virtual void Render() override;

};

