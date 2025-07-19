#include "AstrumOBBColliderComponent.h"

namespace {
	std::pair<AstrumVector2, AstrumVector2> GetAxes(const AstrumOBBColliderComponent& self) {
		const float rotation = DirectX::XMConvertToRadians(self.GetOwner()->GetAbsoluteRotation().Z);
		const float c = cos(rotation), s = sin(rotation);

		return {
			AstrumVector2(c, s),
			AstrumVector2(-s, c)
		};
	}

	std::pair<float, float> GetProjection(const AstrumVector2& axis, const AstrumRotatedRect& rect) {
		float min = std::numeric_limits<float>::max();
		float max = std::numeric_limits<float>::lowest();
		for (const auto& point : { rect.LeftBottom, rect.RightBottom, rect.RightTop, rect.LeftTop }) {
			float projection = point.Dot(axis);
			min = std::min(min, projection);
			max = std::max(max, projection);
		}
		return { min, max };
	}

	bool IsSeparatingAxis(const AstrumRotatedRect& a, const AstrumRotatedRect& b, AstrumVector2 axis) {
		auto obb1 = GetProjection(axis, a);
		auto obb2 = GetProjection(axis, b);

		return obb1.second < obb2.first || obb2.second < obb1.first;
	}
}

AstrumRotatedRect AstrumOBBColliderComponent::GetRotatedRect() const
{
	const auto axes = GetAxes(*this);

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

bool AstrumOBBColliderComponent::IsOverlap(const AstrumOBBColliderComponent& other) const
{
	const auto axes1 = GetAxes(*this);
	const auto axes2 = GetAxes(other);

	const auto rect1 = GetRotatedRect();
	const auto rect2 = other.GetRotatedRect();

	for (const auto& axis : { axes1.first, axes1.second, axes2.first, axes2.second }) {
		if (IsSeparatingAxis(rect1, rect2, axis)) {
			return false;
		}
	}

	return true;
}

bool AstrumOBBColliderComponent::IsOverlap(const AstrumAABBColliderComponent& other) const {
	const auto axes1 = GetAxes(*this);
	const std::pair<AstrumVector2, AstrumVector2> axes2 = { {1.f,0.f},{0.f,1.f} };

	const auto rect1 = GetRotatedRect();
	const auto rect2 = static_cast<AstrumRotatedRect>(other.GetRect());
	
	for (const auto& axis : { axes1.first, axes1.second, axes2.first, axes2.second }) {
		if (IsSeparatingAxis(rect1, rect2, axis)) {
			return false;
		}
	}

	return true;
}

bool AstrumOBBColliderComponent::IsOverlap(const class AstrumCircleColliderComponent& other) const {
    const auto axes = GetAxes(*this);
    const AstrumVector2 center = static_cast<AstrumVector2>(GetOwner()->GetAbsolutePosition());
    const float halfWidth = GetOwner()->GetAbsoluteScale().X * 0.5f;
    const float halfHeight = GetOwner()->GetAbsoluteScale().Y * 0.5f;
    
    const AstrumCircle circle = other.GetCircle();
    
    const AstrumVector2 diff = circle.Center - center;
    const float localX = diff.Dot(axes.first);
    const float localY = diff.Dot(axes.second);
    
    const float clampedX = std::max(-halfWidth, std::min(halfWidth, localX));
    const float clampedY = std::max(-halfHeight, std::min(halfHeight, localY));

    const float dx = localX - clampedX;
    const float dy = localY - clampedY;
    
    return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
}