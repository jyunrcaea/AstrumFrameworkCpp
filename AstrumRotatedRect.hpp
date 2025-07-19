#pragma once
#include "AstrumVector2.hpp"
#include "AstrumRect.hpp"

struct AstrumRotatedRect
{
    constexpr AstrumRotatedRect(
        AstrumVector2 leftBottom,
        AstrumVector2 rightBottom,
        AstrumVector2 rightTop,
        AstrumVector2 leftTop
    ) : LeftBottom(leftBottom), RightBottom(rightBottom), RightTop(rightTop), LeftTop(leftTop) { };

    AstrumVector2 LeftBottom;
    AstrumVector2 RightBottom;
    AstrumVector2 RightTop;
    AstrumVector2 LeftTop;

    explicit AstrumRotatedRect(const AstrumRect& rect);
};