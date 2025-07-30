#include "AstrumAABBColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

class AstrumCollisionSystemSingleton;

AstrumRect AstrumAABBColliderComponent::GetRect() const
{
	const auto& position = GetOwner()->GetAbsolutePosition();
	const auto halfScale = GetOwner()->GetAbsoluteScale() / 2;
	return {
		AstrumVector2 { position.X - halfScale.X, position.Y - halfScale.Y },
		AstrumVector2 { position.X + halfScale.X, position.Y + halfScale.Y }
	};
}

bool AstrumAABBColliderComponent::IsOverlap(AstrumColliderComponent* other) { return other->IsOverlapToAABB(this); }
bool AstrumAABBColliderComponent::IsOverlapToAABB(IAstrumAABBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToAABB(this, other); }
bool AstrumAABBColliderComponent::IsOverlapToOBB(IAstrumOBBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToOBB(this, other); }
bool AstrumAABBColliderComponent::IsOverlapToCircle(IAstrumCircleColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToCircle(this, other); }