#pragma once
#include "AstrumColliderComponent.hpp"
#include "IAstrumCircleColliderComponent.hpp"
#include "AstrumAABBColliderComponent.hpp"

class AstrumCircleColliderComponent : public AstrumColliderComponent, public IAstrumCircleColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_Circle; }
	virtual AstrumCircle GetCircle() const;

	virtual bool IsOverlap(IAstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;

	virtual bool IsOverlapToPoint(AstrumVector2 point) override;

public:
	static std::shared_ptr<AstrumCircleColliderComponent> MakeShared() {
		return std::make_shared<AstrumCircleColliderComponent>();
	}
};