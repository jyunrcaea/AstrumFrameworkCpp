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

protected:
    std::shared_ptr<AstrumRenderPolygonsComponent> renderPolygonsComponent = std::make_shared<AstrumRenderPolygonsComponent>();
};