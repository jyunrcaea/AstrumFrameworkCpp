#pragma once
#include <memory>
#include "../Objects/AstrumObject.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

// 도형 객체
class AstrumShapeObject : public AstrumObject {
public:
    AstrumShapeObject() {
        AddComponent(renderPolygonsComponent);
    }

    AstrumRenderPolygonsComponent& GetRenderPolygonsComponent() const noexcept { return *renderPolygonsComponent; }
protected:
    std::shared_ptr<AstrumRenderPolygonsComponent> renderPolygonsComponent = AstrumRenderPolygonsComponent::MakeShared();

public:
	static std::shared_ptr<AstrumShapeObject> MakeShared() { return std::make_shared<AstrumShapeObject>(); }
};