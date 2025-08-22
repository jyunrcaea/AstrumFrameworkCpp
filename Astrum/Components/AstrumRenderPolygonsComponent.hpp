#pragma once
#include <memory>
#include "../Meshes/AstrumPolygons.hpp"
#include "../Components/AstrumRenderComponent.hpp"

namespace Astrum
{
	class RenderPolygonsComponent : public RenderComponent
	{
	public:
		RenderPolygonsComponent();
		RenderPolygonsComponent(const std::shared_ptr<Polygons>& polygons);
		RenderPolygonsComponent(std::shared_ptr<Polygons>&& polygons);

		std::shared_ptr<Polygons> Polygons = nullptr;

		virtual std::shared_ptr<struct IShaderSetup> GetDefaultShaderPipeline() const override;

	protected:
		virtual void PreRender() override;
		virtual void Render() override;

	public:
		static std::shared_ptr<RenderPolygonsComponent> MakeShared() { return std::make_shared<RenderPolygonsComponent>(); }
		static std::shared_ptr<RenderPolygonsComponent> MakeShared(const std::shared_ptr<Polygons>& polygons) { return std::make_shared<RenderPolygonsComponent>(polygons); }
		static std::shared_ptr<RenderPolygonsComponent> MakeShared(std::shared_ptr<Polygons>&& polygons) { return std::make_shared<RenderPolygonsComponent>(std::move(polygons)); }
	};
}

