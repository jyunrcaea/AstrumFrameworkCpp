#include "AstrumCircleColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

AstrumCircle AstrumCircleColliderComponent::GetCircle() const
{
	return AstrumCircle(
		static_cast<AstrumVector2>(GetOwner()->GetAbsolutePosition()),
		GetOwner()->GetAbsoluteScale().GetMinimum() * 0.5f
	);
}

bool AstrumCircleColliderComponent::IsOverlap(AstrumColliderComponent* other) { return other->IsOverlapToCircle(this); }
bool AstrumCircleColliderComponent::IsOverlapToAABB(IAstrumAABBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToCircle(other, this); }
bool AstrumCircleColliderComponent::IsOverlapToOBB(IAstrumOBBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapCircleToOBB(this, other); }
bool AstrumCircleColliderComponent::IsOverlapToCircle(IAstrumCircleColliderComponent* other) { return AstrumCollisionSystem::IsOverlapCircleToCircle(other, this); }