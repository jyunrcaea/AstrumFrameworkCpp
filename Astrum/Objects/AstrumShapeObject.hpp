#pragma once
#include <memory>
#include "../Objects/AstrumObject.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

namespace Astrum
{
	// 도형 객체
	class ShapeObject : public Object {
	public:
		ShapeObject() {
			AddComponent(renderPolygonsComponent);
		}

		RenderPolygonsComponent& GetRenderPolygonsComponent() const noexcept { return *renderPolygonsComponent; }
	protected:
		std::shared_ptr<RenderPolygonsComponent> renderPolygonsComponent = RenderPolygonsComponent::MakeShared();
	};
}