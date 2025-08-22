#pragma once
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumVector4.hpp"
#include "../Units/AstrumColor.hpp"

namespace Astrum
{
	struct VertexColor {
		Vector3 Position;
		Vector4 Color;

		constexpr VertexColor() = default;
		constexpr VertexColor(const Vector3& pos, const Vector4& col) : Position(pos), Color(col) {}
		constexpr VertexColor(const Vector3& pos, const Color& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
		constexpr VertexColor(Vector3&& pos, Color&& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
		constexpr VertexColor(Vector3&& pos, const Color& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
		constexpr VertexColor(const Vector3& pos, Color&& col) : Position(pos), Color(col.Red, col.Green, col.Blue, col.Alpha) { }
	};
}