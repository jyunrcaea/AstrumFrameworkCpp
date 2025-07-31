#pragma once
#include <memory>
#include "../Meshes/AstrumPolygons.hpp"
#include "../Components/AstrumRenderComponent.hpp"

class AstrumRenderPolygonsComponent : public AstrumRenderComponent
{
public:
	std::shared_ptr<AstrumPolygons> Polygons = nullptr;

	virtual std::shared_ptr<struct IAstrumShaderSetup> GetDefaultShaderPipeline() const override;

protected:
	virtual void PreRender() override;
	virtual void Render() override;

};

