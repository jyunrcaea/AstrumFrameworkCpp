#pragma once
#include "../Vectors/AstrumVector2.hpp"

struct AstrumCircle {
	AstrumVector2 Center;
	float Radius;
};

struct IAstrumCircleColliderComponent {
	virtual ~IAstrumCircleColliderComponent() = default;
	virtual AstrumCircle GetCircle() const = 0;
};