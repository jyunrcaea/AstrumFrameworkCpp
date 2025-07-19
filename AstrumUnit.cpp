#include "AstrumUnit.hpp"
constexpr AstrumRotatedRect::AstrumRotatedRect(AstrumVector2 leftBottom, AstrumVector2 rightBottom, AstrumVector2 rightTop, AstrumVector2 leftTop)
    : LeftBottom(leftBottom), RightBottom(rightBottom), RightTop(rightTop), LeftTop(leftTop)
{
}

AstrumRotatedRect::AstrumRotatedRect(const AstrumRect& rect)
{
    LeftBottom = rect.LeftBottom;
    RightTop = rect.RightTop;
    RightBottom = { rect.RightTop.X, rect.LeftBottom.Y };
    LeftTop = { rect.LeftBottom.X, rect.RightTop.Y };
}