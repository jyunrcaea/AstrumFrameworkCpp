#include "AstrumDrawableObject.hpp"
#include "AstrumVertexColor.hpp"
#include "AstrumPolygons.hpp"

class AstrumCircleObject : public AstrumDrawableObject {
public:
    AstrumCircleObject(const AstrumVertexColor& center, float radius);

protected:
    virtual void Render() override;

private:
    std::unique_ptr<AstrumPolygons> circlePolygon;
};