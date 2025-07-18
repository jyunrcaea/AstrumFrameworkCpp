#include "AstrumRotatedRect.hpp"

AstrumRotatedRect::AstrumRotatedRect(const AstrumRect& rect)
{
    LeftBottom = rect.LeftBottom;
    RightTop = rect.RightTop;
    RightBottom = { rect.RightTop.X, rect.LeftBottom.Y };
    LeftTop = { rect.LeftBottom.X, rect.RightTop.Y };
}