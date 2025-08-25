#pragma once
#include "IAstrumAABBColliderComponent.hpp"
#include "IAstrumOBBColliderComponent.hpp"
#include "IAstrumCircleColliderComponent.hpp"
#include "../Vectors/AstrumVector2.hpp"

enum AstrumColliderType
{
	AstrumColliderType_None = 0,
	AstrumColliderType_AABB,
	AstrumColliderType_Circle,
	AstrumColliderType_OBB,
	AstrumColliderType_Count
};

struct IAstrumColliderComponent
{
public:
	virtual ~IAstrumColliderComponent() = default;

	virtual AstrumColliderType GetColliderType() const = 0;

	// 더블 디스패치 디자인 패턴이 적용되어 타입 안전하게 적절한 충돌 로직을 사용해 닿았는지 판정하는 함수.
	virtual bool IsOverlap(IAstrumColliderComponent* other) = 0;
	virtual bool IsOverlapToAABB(IAstrumAABBColliderComponent* other) = 0;
	virtual bool IsOverlapToOBB(IAstrumOBBColliderComponent* other) = 0;
	virtual bool IsOverlapToCircle(IAstrumCircleColliderComponent* other) = 0;

	virtual bool IsOverlapToPoint(AstrumVector2 point) = 0;
};