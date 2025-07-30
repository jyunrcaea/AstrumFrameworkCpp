#pragma once
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumRectanglePolygons.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

// 직사각형 객체
class AstrumRectangleObject : public AstrumShapeObject
{
public:
    AstrumRectangleObject();
    AstrumRectangleObject(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon);
    AstrumRectangleObject(float width, float height, const AstrumColor& color);

    virtual void Draw() override;

    std::shared_ptr<AstrumRectanglePolygons> GetRectanglePolygons() const;
    void SetRectanglePolygons(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon);

private:
    std::shared_ptr<AstrumRectanglePolygons> rectanglePolygon = nullptr;

public:
    static std::shared_ptr<AstrumRectangleObject> MakeShared() { return std::make_shared<AstrumRectangleObject>(); }
    static std::shared_ptr<AstrumRectangleObject> MakeShared(const std::shared_ptr<AstrumRectanglePolygons>& rectanglePolygon) { return std::make_shared<AstrumRectangleObject>(rectanglePolygon); }
    static std::shared_ptr<AstrumRectangleObject> MakeShared(float width, float height, const AstrumColor & color) {
        return std::make_shared<AstrumRectangleObject>(width, height, color);
    }
};