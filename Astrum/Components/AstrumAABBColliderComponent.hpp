#pragma once
#include <memory>
#include <functional>
#include "AstrumColliderComponent.hpp"
#include "IAstrumAABBColliderComponent.hpp"

class AstrumAABBColliderComponent : public AstrumColliderComponent, public IAstrumAABBColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_AABB; }
	// 충돌체의 AABB를 반환합니다. GetRectFunction이 설정되어 있으면 해당 함수를 호출하고, 아니면 소유자 객체의 위치와 스케일을 사용해 계산합니다.
	virtual AstrumRect GetRect() const;

	virtual bool IsOverlap(IAstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;

	virtual bool IsOverlapToPoint(AstrumVector2 point) override;

	std::function<AstrumRect()> GetRectFunction = nullptr;
public:
	static std::shared_ptr<AstrumAABBColliderComponent> MakeShared() {
		return std::make_shared<AstrumAABBColliderComponent>();
	}
};