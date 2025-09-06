#pragma once
#include <algorithm>
#include <cmath>
#include <memory>
#include <functional>
#include <DirectXMath.h>
#include "AstrumColliderComponent.hpp"
#include "AstrumAABBColliderComponent.hpp"
#include "AstrumCircleColliderComponent.hpp"
#include "IAstrumOBBColliderComponent.hpp"

class AstrumOBBColliderComponent : public AstrumColliderComponent, public IAstrumOBBColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_OBB; }
	// 충돌체의 OBB를 반환합니다. GetRotatedRectFunction이 설정되어 있으면 해당 함수를 호출하고, 아니면 소유자 객체의 위치와 스케일, 회전을 사용해 계산합니다.
	virtual AstrumRotatedRect GetRotatedRect() const;
	virtual AstrumCenterHalfRect GetCenterHalfRect() const override;
	virtual std::pair<AstrumVector2, AstrumVector2> GetAxes() const override;

	virtual bool IsOverlap(IAstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;

	virtual bool IsOverlapToPoint(AstrumVector2 point) override;

	std::function<AstrumRotatedRect()> GetRotatedRectFunction = nullptr;
public:
	static std::shared_ptr<AstrumOBBColliderComponent> MakeShared() {
		return std::make_shared<AstrumOBBColliderComponent>();
	}
};