#pragma once
#include <memory>
#include <functional>
#include "AstrumColliderComponent.hpp"
#include "IAstrumCircleColliderComponent.hpp"
#include "AstrumAABBColliderComponent.hpp"

class AstrumCircleColliderComponent : public AstrumColliderComponent, public IAstrumCircleColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_Circle; }
	// 충돌체의 원을 반환합니다. GetCircleFunction이 설정되어 있으면 해당 함수를 호출하고, 아니면 소유자 객체의 위치와 스케일을 사용해 계산합니다.
	virtual AstrumCircle GetCircle() const;

	virtual bool IsOverlap(IAstrumColliderComponent* other) override;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) override;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) override;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) override;

	virtual bool IsOverlapToPoint(AstrumVector2 point) override;

	std::function<AstrumCircle()> GetCircleFunction = nullptr;
public:
	static std::shared_ptr<AstrumCircleColliderComponent> MakeShared() {
		return std::make_shared<AstrumCircleColliderComponent>();
	}
};