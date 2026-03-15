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
    static double EaseInCubic(double x) noexcept { return x * x * x; }
    static double EaseOutCubic(double x) noexcept { x = 1.0 - x; return 1.0 - x * x * x; }
    static double EaseInOutCubic(double x) noexcept { return x < 0.5 ? 4.0 * x * x * x : 1.0 - std::pow(-2.0 * x + 2.0, 3.0) * 0.5; }

    static double EaseInQuart(double x) noexcept { return x * x * x * x; }
    static double EaseOutQuart(double x) noexcept { x = 1.0 - x; return 1.0 - x * x * x * x; }
    static double EaseInOutQuart(double x) noexcept { return x < 0.5 ? 8.0 * x * x * x * x : 1.0 - std::pow(-2.0 * x + 2.0, 4.0) * 0.5; }

    static double EaseInQuint(double x) noexcept { return x * x * x * x * x; }
    static double EaseOutQuint(double x) noexcept { x = 1.0 - x; return 1.0 - x * x * x * x * x; }
    static double EaseInOutQuint(double x) noexcept { return x < 0.5 ? 16.0 * std::pow(x, 5.0) : 1.0 - std::pow(-2.0 * x + 2.0, 5.0) * 0.5; }

    static double EaseInExpo(double x) noexcept { return x == 0.0 ? 0.0 : std::pow(2.0, 10.0 * x - 10.0); }
    static double EaseOutExpo(double x) noexcept { return x == 1.0 ? 1.0 : 1.0 - std::pow(2.0, -10.0 * x); }
    static double EaseInOutExpo(double x) noexcept {
        if (x == 0.0) return 0.0;
        if (x == 1.0) return 1.0;
        return x < 0.5 ? std::pow(2.0, 20.0 * x - 10.0) * 0.5 : (2.0 - std::pow(2.0, -20.0 * x + 10.0)) * 0.5;
    }

    static double EaseInCirc(double x) noexcept { return 1.0 - std::sqrt(1.0 - x * x); }
    static double EaseOutCirc(double x) noexcept { return std::sqrt(1.0 - std::pow(x - 1.0, 2.0)); }
    static double EaseInOutCirc(double x) noexcept { return x < 0.5 ? (1.0 - std::sqrt(1.0 - std::pow(2.0 * x, 2.0))) * 0.5 : (std::sqrt(1.0 - std::pow(-2.0 * x + 2.0, 2.0)) + 1.0) * 0.5; }

    static double EaseInBack(double x) noexcept { const double c1 = 1.70158; const double c3 = c1 + 1.0; return c3 * x * x * x - c1 * x * x; }
    static double EaseOutBack(double x) noexcept { const double c1 = 1.70158; const double c3 = c1 + 1.0; x = x - 1.0; return 1.0 + c3 * x * x * x + c1 * x * x; }
    static double EaseInOutBack(double x) noexcept { const double c1 = 1.70158; const double c2 = c1 * 1.525; if (x < 0.5) { return (std::pow(2.0 * x, 2.0) * ((c2 + 1.0) * 2.0 * x - c2)) * 0.5; } else { double t = 2.0 * x - 2.0; return (std::pow(t, 2.0) * ((c2 + 1.0) * t + c2) + 2.0) * 0.5; } }

    static double EaseInElastic(double x) noexcept {
        if (x == 0.0) return 0.0;
        if (x == 1.0) return 1.0;
        const double c4 = (2.0 * std::numbers::pi) / 3.0;
        return -std::pow(2.0, 10.0 * x - 10.0) * std::sin((x * 10.0 - 10.75) * c4);
    }
    static double EaseOutElastic(double x) noexcept {
        if (x == 0.0) return 0.0;
        if (x == 1.0) return 1.0;
        const double c4 = (2.0 * std::numbers::pi) / 3.0;
        return std::pow(2.0, -10.0 * x) * std::sin((x * 10.0 - 0.75) * c4) + 1.0;
    }
    static double EaseInOutElastic(double x) noexcept {
        if (x == 0.0) return 0.0;
        if (x == 1.0) return 1.0;
        const double c5 = (2.0 * std::numbers::pi) / 4.5;
        if (x < 0.5) {
            return -0.5 * std::pow(2.0, 20.0 * x - 10.0) * std::sin((20.0 * x - 11.125) * c5);
        } else {
            return std::pow(2.0, -20.0 * x + 10.0) * std::sin((20.0 * x - 11.125) * c5) * 0.5 + 1.0;
        }
    }

    // Bounce helpers
    static double EaseOutBounce(double x) noexcept {
        const double n1 = 7.5625;
        const double d1 = 2.75;
        if (x < 1.0 / d1) {
            return n1 * x * x;
        } else if (x < 2.0 / d1) {
            x -= 1.5 / d1;
            return n1 * x * x + 0.75;
        } else if (x < 2.5 / d1) {
            x -= 2.25 / d1;
            return n1 * x * x + 0.9375;
        } else {
            x -= 2.625 / d1;
            return n1 * x * x + 0.984375;
        }
    }
    static double EaseInBounce(double x) noexcept { return 1.0 - EaseOutBounce(1.0 - x); }
    static double EaseInOutBounce(double x) noexcept { return x < 0.5 ? (1.0 - EaseOutBounce(1.0 - 2.0 * x)) * 0.5 : (1.0 + EaseOutBounce(2.0 * x - 1.0)) * 0.5; }

    // Smoothstep variants
    static double SmoothStep(double x) noexcept { return x * x * (3.0 - 2.0 * x); }
    static double SmootherStep(double x) noexcept { return x * x * x * (x * (x * 6.0 - 15.0) + 10.0); }
};