#include <vector>
#include "AstrumShapeObject.hpp"
#include "../Meshes/AstrumCirclePolygons.hpp"
#include "../Components/AstrumRenderPolygonsComponent.hpp"

class AstrumCircleObject : public AstrumShapeObject {
public:
    AstrumCircleObject();
    AstrumCircleObject(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon);
    AstrumCircleObject(const AstrumVertexColor& center, float radius, const unsigned short segment = 128);

    std::shared_ptr<AstrumCirclePolygons> GetCirclePolygons() const;
    void SetCirclePolygons(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon);

private:
    std::shared_ptr<AstrumCirclePolygons> circlePolygon;
};