#pragma once
#include "IAstrumAABBColliderComponent.hpp"
#include "IAstrumOBBColliderComponent.hpp"
#include "IAstrumCircleColliderComponent.hpp"
#include "../Vectors/AstrumVector2.hpp"

namespace Astrum {
	enum class ColliderType
	{
		None = 0,
		AABB,
		Circle,
		OBB,
		Count
	};

	struct IAABBColliderComponent;
	struct IOBBColliderComponent;
	struct ICircleColliderComponent;

	struct IColliderComponent
	{
	public:
		virtual ~IColliderComponent() = default;

		virtual ColliderType GetColliderType() const = 0;

		// 더블 디스패치 디자인 패턴이 적용되어 타입 안전하게 적절한 충돌 로직을 사용해 닿았는지 판정하는 함수.
		virtual bool IsOverlap(IColliderComponent* other) = 0;
		virtual bool IsOverlapToAABB(IAABBColliderComponent* other) = 0;
		virtual bool IsOverlapToOBB(IOBBColliderComponent* other) = 0;
		virtual bool IsOverlapToCircle(ICircleColliderComponent* other) = 0;

		virtual bool IsOverlapToPoint(Vector2 point) = 0;
	};
}