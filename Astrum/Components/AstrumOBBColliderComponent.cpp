#include "AstrumOBBColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

std::pair<AstrumVector2, AstrumVector2> AstrumOBBColliderComponent::GetAxes() const
{
	const float rotation = DirectX::XMConvertToRadians(GetOwner()->GetAbsoluteRotation().Z);
	const float c = cos(rotation), s = sin(rotation);

	return {
		AstrumVector2(c, s),
		AstrumVector2(-s, c)
	};
}

AstrumRotatedRect AstrumOBBColliderComponent::GetRotatedRect() const
{
	const auto axes = this->GetAxes();

	AstrumVector2 xAxis = axes.first * GetOwner()->GetAbsoluteScale().X / 2;
	AstrumVector2 yAxis = axes.second * GetOwner()->GetAbsoluteScale().Y / 2;
	AstrumVector2 center = static_cast<AstrumVector2>(GetOwner()->GetAbsolutePosition());

	return {
		center - xAxis - yAxis,
		center + xAxis - yAxis,
		center + xAxis + yAxis,
		center - xAxis + yAxis
	};
}

AstrumCenterHalfRect AstrumOBBColliderComponent::GetCenterHalfRect() const
{
	return AstrumCenterHalfRect{
		static_cast<AstrumVector2>(GetOwner()->GetAbsolutePosition()),
		GetOwner()->GetAbsoluteScale().X * 0.5f,
		GetOwner()->GetAbsoluteScale().Y * 0.5f
	};
}

bool AstrumOBBColliderComponent::IsOverlap(IAstrumColliderComponent* other) { return other->IsOverlapToOBB(this); }
bool AstrumOBBColliderComponent::IsOverlapToAABB(IAstrumAABBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapAABBToOBB(other, this); }
bool AstrumOBBColliderComponent::IsOverlapToOBB(IAstrumOBBColliderComponent* other) { return AstrumCollisionSystem::IsOverlapOBBToOBB(other, this); }
bool AstrumOBBColliderComponent::IsOverlapToCircle(IAstrumCircleColliderComponent* other) { return AstrumCollisionSystem::IsOverlapCircleToOBB(other, this); }

bool AstrumOBBColliderComponent::IsOverlapToPoint(AstrumVector2 point) {
	const auto& [center, halfWidth, halfHeight] = GetCenterHalfRect();

	const auto rotated = center.Rotate(point, -GetOwner()->GetAbsoluteRotation().Z);
	return fabs(rotated.X - point.X) <= halfWidth && fabs(rotated.Y - point.Y) <= halfHeight;
}