#pragma once
#include "../Vectors/AstrumVector2.hpp"
#include "IAstrumAABBColliderComponent.hpp"

struct AstrumRotatedRect
{
    constexpr AstrumRotatedRect(
        AstrumVector2 leftBottom,
        AstrumVector2 rightBottom,
        AstrumVector2 rightTop,
        AstrumVector2 leftTop
    ) : LeftBottom(leftBottom), RightBottom(rightBottom), RightTop(rightTop), LeftTop(leftTop) {
    };

    AstrumVector2 LeftBottom;
    AstrumVector2 RightBottom;
    AstrumVector2 RightTop;
    AstrumVector2 LeftTop;

    inline explicit AstrumRotatedRect(const AstrumRect& rect) {
        LeftBottom = rect.LeftBottom;
        RightTop = rect.RightTop;
        RightBottom = { rect.RightTop.X, rect.LeftBottom.Y };
        LeftTop = { rect.LeftBottom.X, rect.RightTop.Y };
    }
};

struct AstrumCenterHalfRect {
    AstrumVector2 Center;
    float HalfWidth;
    float HalfHeight;
};

struct IAstrumOBBColliderComponent {
	virtual ~IAstrumOBBColliderComponent() = default;
	virtual AstrumRotatedRect GetRotatedRect() const = 0;
    virtual AstrumCenterHalfRect GetCenterHalfRect() const = 0;
	virtual std::pair<AstrumVector2, AstrumVector2> GetAxes() const = 0;
};