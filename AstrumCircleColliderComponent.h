#pragma once
#include "AstrumColliderComponent.h"
#include "AstrumCircle.hpp"
#include "AstrumAABBColliderComponent.h"

class AstrumCircleColliderComponent : public AstrumColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_Circle; }
	virtual AstrumCircle GetCircle() const;

	bool IsOverlap(const AstrumCircleColliderComponent& other) const;
	bool IsOverlap(const AstrumAABBColliderComponent& other) const;
};