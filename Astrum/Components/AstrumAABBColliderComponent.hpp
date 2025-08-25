#pragma once
#include <memory>
#include "AstrumColliderComponent.hpp"
#include "IAstrumAABBColliderComponent.hpp"

class AstrumAABBColliderComponent : public AstrumColliderComponent, public IAstrumAABBColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_AABB; }
	virtual AstrumRect GetRect() const;

	virtual bool IsOverlap(IAstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;

	virtual bool IsOverlapToPoint(AstrumVector2 point) override;

public:
	static std::shared_ptr<AstrumAABBColliderComponent> MakeShared() {
		return std::make_shared<AstrumAABBColliderComponent>();
	}
};