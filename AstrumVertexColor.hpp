#pragma once
#include "AstrumVector3.hpp"
#include "AstrumVector4.hpp"
#include "AstrumColor.hpp"

struct AstrumVertexColor {
    AstrumVector3 Position;
    AstrumVector4 Color;

    AstrumVertexColor() = default;
    AstrumVertexColor(const AstrumVector3& pos, const AstrumVector4& col) : Position(pos), Color(col) {}
    AstrumVertexColor(const AstrumVector3& pos, const AstrumColor& col)
        : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) {
    }
    AstrumVertexColor(AstrumVector3&& pos, AstrumColor&& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
    AstrumVertexColor(AstrumVector3&& pos, const AstrumColor& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
    AstrumVertexColor(const AstrumVector3& pos, AstrumColor&& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
};