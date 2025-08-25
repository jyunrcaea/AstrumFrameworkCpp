#include "AstrumRenderPolygonsComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumRenderPolygonsComponent::AstrumRenderPolygonsComponent() { }
AstrumRenderPolygonsComponent::AstrumRenderPolygonsComponent(const std::shared_ptr<AstrumPolygons>& polygons)
	: Polygons(polygons) { }
AstrumRenderPolygonsComponent::AstrumRenderPolygonsComponent(std::shared_ptr<AstrumPolygons>&& polygons)
	: Polygons(std::move(polygons)) {}

std::shared_ptr<struct IAstrumShaderSetup> AstrumRenderPolygonsComponent::GetDefaultShaderPipeline() const {
	return AstrumRenderer::Instance().DefaultShapeShaderPipeline;
}

void AstrumRenderPolygonsComponent::PreRender() {
	if (nullptr == Polygons) return;

	AstrumRenderComponent::PreRender();
}

void AstrumRenderPolygonsComponent::Render() {
	if (nullptr == Polygons) return;
 
	AstrumRenderComponent::Render();
	Polygons->Render();
}
