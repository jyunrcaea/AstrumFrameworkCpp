#pragma once
#include <algorithm>
#include <cmath>
#include <DirectXMath.h>
#include "AstrumColliderComponent.hpp"
#include "AstrumAABBColliderComponent.hpp"
#include "AstrumCircleColliderComponent.hpp"
#include "IAstrumOBBColliderComponent.hpp"

class AstrumOBBColliderComponent : public AstrumColliderComponent, public IAstrumOBBColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_OBB; }
	virtual AstrumRotatedRect GetRotatedRect() const;
	virtual AstrumCenterHalfRect GetCenterHalfRect() const override;
	virtual std::pair<AstrumVector2, AstrumVector2> GetAxes() const override;

	virtual bool IsOverlap(IAstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;

	virtual bool IsOverlapToPoint(AstrumVector2 point) override;
public:
	static std::shared_ptr<AstrumOBBColliderComponent> MakeShared() {
		return std::make_shared<AstrumOBBColliderComponent>();
	}
};