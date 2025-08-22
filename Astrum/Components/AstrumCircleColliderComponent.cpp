#include "AstrumCircleColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

namespace Astrum {
	Circle CircleColliderComponent::GetCircle() const
	{
		return Circle(
			static_cast<Vector2>(GetOwner()->GetAbsolutePosition()),
			GetOwner()->GetAbsoluteScale().GetMinimum() * 0.5f
		);
	}

	bool CircleColliderComponent::IsOverlap(IColliderComponent* other) { return other->IsOverlapToCircle(this); }
	bool CircleColliderComponent::IsOverlapToAABB(IAABBColliderComponent* other) { return CollisionSystem::IsOverlapAABBToCircle(other, this); }
	bool CircleColliderComponent::IsOverlapToOBB(IOBBColliderComponent* other) { return CollisionSystem::IsOverlapCircleToOBB(this, other); }
	bool CircleColliderComponent::IsOverlapToCircle(ICircleColliderComponent* other) { return CollisionSystem::IsOverlapCircleToCircle(other, this); }

	bool CircleColliderComponent::IsOverlapToPoint(Vector2 point) {
		const auto& [center, radius] = GetCircle();
		return point.Distance(center) <= radius;
	}
}
