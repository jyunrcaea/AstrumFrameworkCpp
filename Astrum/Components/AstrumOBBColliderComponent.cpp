#include "AstrumOBBColliderComponent.hpp"
#include "../Singletons/AstrumCollisionSystem.hpp"

namespace Astrum {
	std::pair<Vector2, Vector2> OBBColliderComponent::GetAxes() const
	{
		const float rotation = DirectX::XMConvertToRadians(GetOwner()->GetAbsoluteRotation().Z);
		const float c = cos(rotation), s = sin(rotation);

		return {
			Vector2(c, s),
			Vector2(-s, c)
		};
	}

	RotatedRect OBBColliderComponent::GetRotatedRect() const
	{
		const auto axes = this->GetAxes();

		Vector2 xAxis = axes.first * GetOwner()->GetAbsoluteScale().X / 2;
		Vector2 yAxis = axes.second * GetOwner()->GetAbsoluteScale().Y / 2;
		Vector2 center = static_cast<Vector2>(GetOwner()->GetAbsolutePosition());

		return {
			center - xAxis - yAxis,
			center + xAxis - yAxis,
			center + xAxis + yAxis,
			center - xAxis + yAxis
		};
	}

	CenterHalfRect OBBColliderComponent::GetCenterHalfRect() const
	{
		return CenterHalfRect{
			static_cast<Vector2>(GetOwner()->GetAbsolutePosition()),
			GetOwner()->GetAbsoluteScale().X * 0.5f,
			GetOwner()->GetAbsoluteScale().Y * 0.5f
		};
	}

	bool OBBColliderComponent::IsOverlap(IColliderComponent* other) { return other->IsOverlapToOBB(this); }
	bool OBBColliderComponent::IsOverlapToAABB(IAABBColliderComponent* other) { return CollisionSystem::IsOverlapAABBToOBB(other, this); }
	bool OBBColliderComponent::IsOverlapToOBB(IOBBColliderComponent* other) { return CollisionSystem::IsOverlapOBBToOBB(other, this); }
	bool OBBColliderComponent::IsOverlapToCircle(ICircleColliderComponent* other) { return CollisionSystem::IsOverlapCircleToOBB(other, this); }

	bool OBBColliderComponent::IsOverlapToPoint(Vector2 point) {
		const auto& [center, halfWidth, halfHeight] = GetCenterHalfRect();

		const auto rotated = center.Rotate(point, -GetOwner()->GetAbsoluteRotation().Z);
		return fabs(rotated.X - point.X) <= halfWidth && fabs(rotated.Y - point.Y) <= halfHeight;
	}
}