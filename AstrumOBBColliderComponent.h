#pragma once
#include <algorithm>
#include <cmath>
#include <DirectXMath.h>
#include "AstrumColliderComponent.h"
#include "AstrumRotatedRect.hpp"
#include "AstrumAABBColliderComponent.h"
#include "AstrumCircleColliderComponent.h"

class AstrumOBBColliderComponent : public AstrumColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_OBB; }
	virtual AstrumRotatedRect GetRotatedRect() const;

	bool IsOverlap(const AstrumOBBColliderComponent& other) const;
	bool IsOverlap(const class AstrumAABBColliderComponent& other) const;
	bool IsOverlap(const class AstrumCircleColliderComponent& other) const;
};