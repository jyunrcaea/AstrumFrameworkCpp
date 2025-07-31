#include "AstrumRectangleObject.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumRectangleObject::AstrumRectangleObject() {}
AstrumRectangleObject::AstrumRectangleObject(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon) {
    SetRectanglePolygons(rectanglePolygon);
}
AstrumRectangleObject::AstrumRectangleObject(float width, float height, const AstrumColor& color) {
    SetRectanglePolygons(AstrumRectanglePolygons::MakeShared(width, height, color));
}

void AstrumRectangleObject::Draw() {
    if (Visible) {
        AstrumRenderer::Instance().EnqueueRenderable(renderPolygonsComponent);
    }
}

std::shared_ptr<AstrumRectanglePolygons> AstrumRectangleObject::GetRectanglePolygons() const {
    return rectanglePolygon;
}

void AstrumRectangleObject::SetRectanglePolygons(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon) {
    renderPolygonsComponent->Polygons = (this->rectanglePolygon = rectanglePolygon);
}
