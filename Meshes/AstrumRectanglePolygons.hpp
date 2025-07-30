#pragma once
#include <memory>
#include "AstrumPolygons.hpp"

class AstrumRectanglePolygons : public AstrumPolygons
{
public:
	AstrumRectanglePolygons(float width, float height, const AstrumColor& color);
	AstrumRectanglePolygons(const AstrumVertexColor& leftTop, const AstrumVertexColor& rightTop, const AstrumVertexColor& leftBottom, const AstrumVertexColor& rightBottom);

	void SetColor(const AstrumColor& color);
	void SetColor(const AstrumColor& leftTop, const AstrumColor& rightTop, const AstrumColor& leftBottom, const AstrumColor& rightBottom);

public:
	static std::shared_ptr<AstrumRectanglePolygons> MakeShared(float width, float height, const AstrumColor& color) {
		return std::make_shared<AstrumRectanglePolygons>(width, height, color);
	}
	static std::shared_ptr<AstrumRectanglePolygons> MakeShared(const AstrumVertexColor& leftTop, const AstrumVertexColor& rightTop, const AstrumVertexColor& leftBottom, const AstrumVertexColor& rightBottom) {
		return std::make_shared<AstrumRectanglePolygons>(leftTop, rightTop, leftBottom, rightBottom);
	}
};