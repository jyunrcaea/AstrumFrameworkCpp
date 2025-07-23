#pragma once
#include "AstrumColliderComponent.h"
#include "AstrumRect.hpp"

class AstrumAABBColliderComponent : public AstrumColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_AABB; }
	virtual AstrumRect GetRect() const;

	bool IsOverlap(const AstrumAABBColliderComponent& other) const;
};