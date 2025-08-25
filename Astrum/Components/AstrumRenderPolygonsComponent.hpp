#pragma once
#include <memory>
#include "../Meshes/AstrumPolygons.hpp"
#include "../Components/AstrumRenderComponent.hpp"

class AstrumRenderPolygonsComponent : public AstrumRenderComponent
{
public:
	AstrumRenderPolygonsComponent();
	AstrumRenderPolygonsComponent(const std::shared_ptr<AstrumPolygons>& polygons);
	AstrumRenderPolygonsComponent(std::shared_ptr<AstrumPolygons>&& polygons);

	std::shared_ptr<AstrumPolygons> Polygons = nullptr;

	virtual std::shared_ptr<struct IAstrumShaderSetup> GetDefaultShaderPipeline() const override;

protected:
	virtual void PreRender() override;
	virtual void Render() override;

public:
	static std::shared_ptr<AstrumRenderPolygonsComponent> MakeShared() { return std::make_shared<AstrumRenderPolygonsComponent>(); }
	static std::shared_ptr<AstrumRenderPolygonsComponent> MakeShared(const std::shared_ptr<AstrumPolygons>& polygons) { return std::make_shared<AstrumRenderPolygonsComponent>(polygons); }
	static std::shared_ptr<AstrumRenderPolygonsComponent> MakeShared(std::shared_ptr<AstrumPolygons>&& polygons) { return std::make_shared<AstrumRenderPolygonsComponent>(std::move(polygons)); }
};

