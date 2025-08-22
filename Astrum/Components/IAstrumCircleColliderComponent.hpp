#pragma once
#include "../Vectors/AstrumVector2.hpp"

namespace Astrum {
	struct Circle {
		Vector2 Center;
		float Radius;
	};

	struct ICircleColliderComponent {
		virtual ~ICircleColliderComponent() = default;
		virtual Circle GetCircle() const = 0;
	};
}