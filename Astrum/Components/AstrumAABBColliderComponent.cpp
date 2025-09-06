#include "AstrumAABBColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

class AstrumCollisionSystemSingleton;

AstrumRect AstrumAABBColliderComponent::GetRect() const
{
	if (GetRectFunction) {
		return GetRectFunction();
	}

	const auto& position = GetOwner()->GetAbsolutePosition();
	const auto halfScale = GetOwner()->GetAbsoluteScale() / 2;
	return {
		AstrumVector2 { position.X - halfScale.X, position.Y - halfScale.Y },
		AstrumVector2 { position.X + halfScale.X, position.Y + halfScale.Y }
	};
}

bool AstrumAABBColliderComponent::IsOverlap(IAstrumColliderComponent* other) { return other->IsOverlapToAABB(this); }
bool AstrumAABBColliderComponent::IsOverlapToAABB(IAstrumAABBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToAABB(this, other); }
bool AstrumAABBColliderComponent::IsOverlapToOBB(IAstrumOBBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToOBB(this, other); }
bool AstrumAABBColliderComponent::IsOverlapToCircle(IAstrumCircleColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToCircle(this, other); }

bool AstrumAABBColliderComponent::IsOverlapToPoint(AstrumVector2 point) {
	const auto& [leftTop, rightBottom] = GetRect();
	return
		(leftTop.X <= point.X && point.X <= rightBottom.X) &&
		(rightBottom.Y <= point.Y && point.Y <= leftTop.Y);
}
