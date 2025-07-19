#include <vector>
#include "AstrumDrawableObject.hpp"
#include "AstrumVertexColor.hpp"
#include "AstrumPolygons.hpp"
#include "AstrumVector3.hpp"

class AstrumCircleObject : public AstrumDrawableObject {
public:
    AstrumCircleObject(const AstrumVertexColor& center, float radius, const unsigned short segment = 128);
    AstrumCircleObject(const AstrumVertexColor& center, float radius, const std::vector<AstrumColor>& colors, const unsigned short segment = 128);

protected:
    virtual void Render() override;

private:
    std::unique_ptr<AstrumPolygons> circlePolygon;
};