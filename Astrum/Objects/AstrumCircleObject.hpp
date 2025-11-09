#include <vector>
#include <memory>
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

public:
    static std::shared_ptr<AstrumCircleObject> MakeShared() { return std::make_shared<AstrumCircleObject>(); }
    static std::shared_ptr<AstrumCircleObject> MakeShared(const std::shared_ptr<AstrumCirclePolygons>& circlePolygon) { return std::make_shared<AstrumCircleObject>(circlePolygon); }
	static std::shared_ptr<AstrumCircleObject> MakeShared(const AstrumVertexColor& center, float radius, const unsigned short segment = 128) { return std::make_shared<AstrumCircleObject>(center, radius, segment); }
};