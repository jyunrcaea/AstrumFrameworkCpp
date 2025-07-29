#include "AstrumRenderPolygonsComponent.hpp"
#include "AstrumRenderer.hpp"

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
