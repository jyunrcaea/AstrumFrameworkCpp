#pragma once
#include <memory>
#include <functional>
#include "AstrumColliderComponent.hpp"
#include "IAstrumAABBColliderComponent.hpp"

class AstrumAABBColliderComponent : public AstrumColliderComponent, public IAstrumAABBColliderComponent
{
public:
	virtual AstrumColliderType GetColliderType() const override { return AstrumColliderType::AstrumColliderType_AABB; }
	// �浹ü�� AABB�� ��ȯ�մϴ�. GetRectFunction�� �����Ǿ� ������ �ش� �Լ��� ȣ���ϰ�, �ƴϸ� ������ ��ü�� ��ġ�� �������� ����� ����մϴ�.
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