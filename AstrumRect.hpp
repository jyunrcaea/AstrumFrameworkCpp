#pragma once
#include "AstrumVector2.hpp"

struct AstrumRect {
	constexpr AstrumRect() = default;
	constexpr AstrumRect(const AstrumVector2& leftBottom,const AstrumVector2& rightTop) : LeftBottom(leftBottom), RightTop(rightTop) { }

	AstrumVector2 LeftBottom;
	AstrumVector2 RightTop;
};