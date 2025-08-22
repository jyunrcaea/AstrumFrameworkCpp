#pragma once
#include "../Vectors/AstrumVector2.hpp"

namespace Astrum {
	struct Rect {
		constexpr Rect() = default;
		constexpr Rect(const Vector2& leftBottom, const Vector2& rightTop) : LeftBottom(leftBottom), RightTop(rightTop) {}

		Vector2 LeftBottom;
		Vector2 RightTop;
	};

	struct IAABBColliderComponent {
		virtual ~IAABBColliderComponent() = default;
		virtual Rect GetRect() const = 0;
	};
}