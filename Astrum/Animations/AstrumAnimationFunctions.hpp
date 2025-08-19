#pragma once
#include <cmath>
#include <numbers>

class AstrumAnimationFunctions {
public:
	static double Linear(double x) noexcept { return x; }
	static double EaseInSine(double x) noexcept { return 1.0 - std::cos((x * std::numbers::pi) * 0.5); }
	static double EaseOutSine(double x) noexcept { return std::sin((x * std::numbers::pi) * 0.5); }
	static double EaseInOutSine(double x) noexcept { return -(std::cos(std::numbers::pi *x) - 1.0) * 0.5; }
	static double EaseInQuad(double x) noexcept { return x * x; }
	static double EaseOutQuad(double x) noexcept { x = 1.0 - x; return 1.0 - x * x; }
	static double EaseInOutQuad(double x) noexcept { return x < 0.5 ? 2.0 * x * x : 1.0 - std::pow(-2.0 * x + 2.0, 2.0) * 0.5; }
};