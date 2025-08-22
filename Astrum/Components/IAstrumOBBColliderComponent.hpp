#pragma once
#include "../Vectors/AstrumVector2.hpp"
#include "IAstrumAABBColliderComponent.hpp"

namespace Astrum {
	struct RotatedRect
	{
		constexpr RotatedRect(
			Vector2 leftBottom,
			Vector2 rightBottom,
			Vector2 rightTop,
			Vector2 leftTop
		) : LeftBottom(leftBottom), RightBottom(rightBottom), RightTop(rightTop), LeftTop(leftTop) {
		};

		Vector2 LeftBottom;
		Vector2 RightBottom;
		Vector2 RightTop;
		Vector2 LeftTop;

		inline explicit RotatedRect(const Rect& rect) {
			LeftBottom = rect.LeftBottom;
			RightTop = rect.RightTop;
			RightBottom = { rect.RightTop.X, rect.LeftBottom.Y };
			LeftTop = { rect.LeftBottom.X, rect.RightTop.Y };
		}
	};

	struct CenterHalfRect {
		Vector2 Center;
		float HalfWidth;
		float HalfHeight;
	};

	struct IOBBColliderComponent {
		virtual ~IOBBColliderComponent() = default;
		virtual RotatedRect GetRotatedRect() const = 0;
		virtual CenterHalfRect GetCenterHalfRect() const = 0;
		virtual std::pair<Vector2, Vector2> GetAxes() const = 0;
	};
}