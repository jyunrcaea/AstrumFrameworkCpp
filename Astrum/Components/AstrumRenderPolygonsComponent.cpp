#include "AstrumRenderPolygonsComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"

namespace Astrum {
	RenderPolygonsComponent::RenderPolygonsComponent() { }
	RenderPolygonsComponent::RenderPolygonsComponent(const std::shared_ptr<Polygons>& polygons)
		: Polygons(polygons) { }
	RenderPolygonsComponent::RenderPolygonsComponent(std::shared_ptr<Polygons>&& polygons)
		: Polygons(std::move(polygons)) {}

	std::shared_ptr<struct IShaderSetup> RenderPolygonsComponent::GetDefaultShaderPipeline() const {
		return Renderer::Instance().DefaultShapeShaderPipeline;
	}

	void RenderPolygonsComponent::PreRender() {
		if (nullptr == Polygons) return;

		RenderComponent::PreRender();
	}

	void RenderPolygonsComponent::Render() {
		if (nullptr == Polygons) return;
	 
		RenderComponent::Render();
		Polygons->Render();
	}
}
