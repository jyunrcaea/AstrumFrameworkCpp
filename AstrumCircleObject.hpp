#include <vector>
#include "AstrumShapeObject.hpp"
#include "AstrumCirclePolygons.hpp"
#include "AstrumRenderPolygonsComponent.hpp"

class AstrumCircleObject : public AstrumShapeObject {
public:
    AstrumCircleObject();
    AstrumCircleObject(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon);
    AstrumCircleObject(const AstrumVertexColor& center, float radius, const unsigned short segment = 128);

    virtual void Draw() override;

    std::shared_ptr<AstrumCirclePolygons> GetCirclePolygons() const;
    void SetCirclePolygons(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon);

private:
    std::shared_ptr<AstrumCirclePolygons> circlePolygon;
};