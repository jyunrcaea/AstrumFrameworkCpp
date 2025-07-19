#include "AstrumAABBColliderComponent.h"

AstrumRect AstrumAABBColliderComponent::GetRect() const
{
	const auto& position = GetOwner()->GetAbsolutePosition();
	const auto halfScale = GetOwner()->GetAbsoluteScale() / 2;
	return {
		AstrumVector2 { position.X - halfScale.X, position.Y - halfScale.Y },
		AstrumVector2 { position.X + halfScale.X, position.Y + halfScale.Y }
	};
}

bool AstrumAABBColliderComponent::IsOverlap(const AstrumAABBColliderComponent& other) const
{
	auto a = GetRect();
	auto b = other.GetRect();
	float w = std::min(a.RightTop.X, b.RightTop.X) - std::max(a.LeftBottom.X, b.LeftBottom.X);
	float h = std::min(a.RightTop.Y, b.RightTop.Y) - std::max(a.LeftBottom.Y, b.LeftBottom.Y);
	return w >= 0 && h >= 0;
}