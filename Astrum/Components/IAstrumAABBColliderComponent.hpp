#pragma once
#include <iostream>
#include "../Vectors/AstrumVector2.hpp"

struct AstrumRect {
	constexpr AstrumRect() = default;
	constexpr AstrumRect(const AstrumVector2& leftBottom, const AstrumVector2& rightTop) : LeftBottom(leftBottom), RightTop(rightTop) {}

	AstrumVector2 LeftBottom;
	AstrumVector2 RightTop;

	constexpr float GetWidth() const noexcept { return RightTop.X - LeftBottom.X; }
	constexpr float GetHeight() const noexcept { return RightTop.Y - LeftBottom.Y; }
	constexpr AstrumVector2 GetSize() const noexcept { return { GetWidth(), GetHeight() }; }
	constexpr AstrumVector2 GetCenter() const noexcept { return { (LeftBottom.X + RightTop.X) * 0.5f, (LeftBottom.Y + RightTop.Y) * 0.5f }; }

	constexpr AstrumRect operator+(const AstrumVector2& v) const noexcept { return { LeftBottom + v, RightTop + v }; }
	constexpr AstrumRect operator-(const AstrumVector2& v) const noexcept { return { LeftBottom - v, RightTop - v }; }
	AstrumRect& operator+=(const AstrumVector2& v) noexcept { LeftBottom += v; RightTop += v; return *this; }
	AstrumRect& operator-=(const AstrumVector2& v) noexcept { LeftBottom -= v; RightTop -= v; return *this; }
	constexpr bool operator==(const AstrumRect& other) const noexcept { return LeftBottom == other.LeftBottom && RightTop == other.RightTop; }
	constexpr bool operator!=(const AstrumRect& other) const noexcept { return !(*this == other); }

	constexpr bool IsValid() const noexcept { return LeftBottom.X <= RightTop.X && LeftBottom.Y <= RightTop.Y; }

	std::string ToString() const { return std::format("AstrumRect(LeftBottom: {}, RightTop: {})", LeftBottom.ToString(), RightTop.ToString()); }
};

struct IAstrumAABBColliderComponent {
	virtual ~IAstrumAABBColliderComponent() = default;
	virtual AstrumRect GetRect() const = 0;
};

namespace {
	std::ostream& operator<<(std::ostream& os, const AstrumRect& rect) {
		os << rect.ToString();
		return os;
	}
}