#include "AstrumCircleColliderComponent.h"

AstrumCircle AstrumCircleColliderComponent::GetCircle() const
{
	return AstrumCircle(
		static_cast<AstrumVector2>(GetOwner()->GetAbsolutePosition()),
		GetOwner()->GetAbsoluteScale().GetMinimum() * 0.5f
	);
}

bool AstrumCircleColliderComponent::IsOverlap(const AstrumCircleColliderComponent& other) const
{
	auto a = GetCircle();
	auto b = other.GetCircle();

	return a.Center.Distance(b.Center) <= (a.Radius + b.Radius);
}

bool AstrumCircleColliderComponent::IsOverlap(const AstrumAABBColliderComponent& other) const {
    AstrumCircle circle = GetCircle();
    AstrumRect rect = other.GetRect();

    float closestX = std::max(rect.LeftBottom.X, std::min(circle.Center.X, rect.RightTop.X));
    float closestY = std::max(rect.LeftBottom.Y, std::min(circle.Center.Y, rect.RightTop.Y));

    float dx = circle.Center.X - closestX;
    float dy = circle.Center.Y - closestY;
    
    return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
}