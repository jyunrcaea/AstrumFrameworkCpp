#pragma once
#include "AstrumPolygons.hpp"
#include "../Units/AstrumVertexColor.hpp"

class AstrumCirclePolygons : public AstrumPolygons
{
public:
	AstrumCirclePolygons(const AstrumVertexColor& center, float radius, const unsigned short segment = 128);
	AstrumCirclePolygons(const AstrumVertexColor& center, float radius, const std::vector<AstrumColor>& colors, const unsigned short segment = 128);

public:
	static std::shared_ptr<AstrumCirclePolygons> MakeShared(const AstrumVertexColor& center, float radius, const unsigned short segment = 128) {
		return std::make_shared<AstrumCirclePolygons>(center, radius, segment);
	}
	static std::shared_ptr<AstrumCirclePolygons> MakeShared(const AstrumVertexColor& center, float radius, const std::vector<AstrumColor>& colors, const unsigned short segment = 128) {
		return std::make_shared<AstrumCirclePolygons>(center, radius, colors, segment);
	}
};
