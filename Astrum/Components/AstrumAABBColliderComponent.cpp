#include "AstrumAABBColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

namespace Astrum {
	class CollisionSystemSingleton;

	Rect AABBColliderComponent::GetRect() const
	{
		const auto& position = GetOwner()->GetAbsolutePosition();
		const auto halfScale = GetOwner()->GetAbsoluteScale() / 2;
		return {
			Vector2 { position.X - halfScale.X, position.Y - halfScale.Y },
			Vector2 { position.X + halfScale.X, position.Y + halfScale.Y }
		};
	}

	bool AABBColliderComponent::IsOverlap(IColliderComponent* other) { return other->IsOverlapToAABB(this); }
	bool AABBColliderComponent::IsOverlapToAABB(IAABBColliderComponent* other) { return CollisionSystem::IsOverlapAABBToAABB(this, other); }
	bool AABBColliderComponent::IsOverlapToOBB(IOBBColliderComponent* other) { return CollisionSystem::IsOverlapAABBToOBB(this, other); }
	bool AABBColliderComponent::IsOverlapToCircle(ICircleColliderComponent* other) { return CollisionSystem::IsOverlapAABBToCircle(this, other); }

	bool AABBColliderComponent::IsOverlapToPoint(Vector2 point) {
		const auto& [leftTop, rightBottom] = GetRect();
		return
			(leftTop.X <= point.X && point.X <= rightBottom.X) &&
			(rightBottom.Y <= point.Y && point.Y <= leftTop.Y);
	}
}
