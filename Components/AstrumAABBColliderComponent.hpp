#pragma once
#include "AstrumColliderComponent.hpp"
#include "IAstrumAABBColliderComponent.hpp"

class AstrumAABBColliderComponent : public AstrumColliderComponent, public IAstrumAABBColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_AABB; }
	virtual AstrumRect GetRect() const;

	virtual bool IsOverlap(AstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;
};