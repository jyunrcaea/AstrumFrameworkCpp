#pragma once
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumVector4.hpp"
#include "../Units/AstrumColor.hpp"

struct AstrumVertexColor {
    AstrumVector3 Position;
    AstrumVector4 Color;

    constexpr AstrumVertexColor() = default;
    constexpr AstrumVertexColor(const AstrumVector3& pos, const AstrumVector4& col) : Position(pos), Color(col) {}
    constexpr AstrumVertexColor(const AstrumVector3& pos, const AstrumColor& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) {}
    constexpr AstrumVertexColor(AstrumVector3&& pos, AstrumColor&& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) {}
    constexpr AstrumVertexColor(AstrumVector3&& pos, const AstrumColor& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) {}
    constexpr AstrumVertexColor(const AstrumVector3& pos, AstrumColor&& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) {}
};