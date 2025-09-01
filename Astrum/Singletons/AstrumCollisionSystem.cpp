#include "AstrumCollisionSystem.hpp"
#include "../Vectors/AstrumVector2.hpp"
#include "../AstrumException.hpp"

namespace {
	std::pair<float, float> GetProjection(const AstrumVector2& axis, const AstrumRotatedRect& rect) {
		float min = (std::numeric_limits<float>::max)();
		float max = std::numeric_limits<float>::lowest();
		for (const auto& point : { rect.LeftBottom, rect.RightBottom, rect.RightTop, rect.LeftTop }) {
			float projection = point.Dot(axis);
			min = (std::min)(min, projection);
			max = (std::max)(max, projection);
		}
		return { min, max };
	}

	bool IsSeparatingAxis(const AstrumRotatedRect& a, const AstrumRotatedRect& b, AstrumVector2 axis) {
		auto obb1 = GetProjection(axis, a);
		auto obb2 = GetProjection(axis, b);

		return obb1.second < obb2.first || obb2.second < obb1.first;
	}
}

AstrumCollisionSystemSingleton::AstrumCollisionSystemSingleton() {}

void AstrumCollisionSystemSingleton::AddCollider(AstrumColliderComponent* const collider)
{
	if (!collider)
	{
		throw AstrumException("Cannot add a null collider to the collision system.");
	}
	colliders.push_back(collider);
}

bool AstrumCollisionSystemSingleton::RemoveCollider(AstrumColliderComponent* const collider)
{
	if (auto colliderIter = std::remove(colliders.begin(), colliders.end(), collider); colliderIter != colliders.end())
	{
		std::vector<std::pair<AstrumColliderComponent*, AstrumColliderComponent*>> removeTargets;
		for(auto& pair : collidedPairs)
		{
			if (pair.first == collider)
			{
				pair.second->InvokeOnCollisionExit(collider);
				removeTargets.push_back(pair);
			}
			else if (pair.second == collider)
			{
				pair.first->InvokeOnCollisionExit(collider);
				removeTargets.push_back(pair);
			}
		}

		for (auto& pair : removeTargets) {
			collidedPairs.erase(pair);
		}

		colliders.erase(colliderIter, colliders.end());
		return true;
	}
	return false;
}

void AstrumCollisionSystemSingleton::Update()
{
	for (size_t x = 0; x < colliders.size(); x++)
	{
		for (size_t y = x + 1; y < colliders.size(); y++)
		{
			AstrumColliderComponent* colliderX = colliders[x];
			AstrumColliderComponent* colliderY = colliders[y];

			int colliderTypeX = colliderX->GetColliderType();
			int colliderTypeY = colliderY->GetColliderType();

			if (colliderTypeX == AstrumColliderType::AstrumColliderType_None || colliderTypeY == AstrumColliderType::AstrumColliderType_None)
				continue;

			if (colliderTypeX < colliderTypeY)
			{
				std::swap(colliderX, colliderY);
				std::swap(colliderTypeX, colliderTypeY);
			}

			std::pair colliderPair = { colliderX, colliderY };
			bool over = collidedPairs.contains(colliderPair);

			if (bool result = colliderX->IsOverlap(colliderY); result != over) {
				if (result) {
					colliderX->InvokeOnCollisionEnter(colliderY);
					colliderY->InvokeOnCollisionEnter(colliderX);
					collidedPairs.insert(colliderPair);
				}
				else {
					colliderX->InvokeOnCollisionExit(colliderY);
					colliderY->InvokeOnCollisionExit(colliderX);
					collidedPairs.erase(colliderPair);
				}
			}
			//for end.
		}
	}
	//update end.
}

bool AstrumCollisionSystemSingleton::IsOverlapAABBToAABB(IAstrumAABBColliderComponent* aAABB, IAstrumAABBColliderComponent* bAABB) const {
	auto a = aAABB->GetRect();
	auto b = bAABB->GetRect();
	float w = (std::min)(a.RightTop.X, b.RightTop.X) - (std::max)(a.LeftBottom.X, b.LeftBottom.X);
	float h = (std::min)(a.RightTop.Y, b.RightTop.Y) - (std::max)(a.LeftBottom.Y, b.LeftBottom.Y);
	return w >= 0 && h >= 0;
}

bool AstrumCollisionSystemSingleton::IsOverlapCircleToCircle(IAstrumCircleColliderComponent* aCircle, IAstrumCircleColliderComponent* bCircle) const {
	auto a = aCircle->GetCircle();
	auto b = bCircle->GetCircle();

	return a.Center.Distance(b.Center) <= (a.Radius + b.Radius);
}

bool AstrumCollisionSystemSingleton::IsOverlapAABBToCircle(IAstrumAABBColliderComponent* aAABB, IAstrumCircleColliderComponent* bCircle) const {
	AstrumRect rect = aAABB->GetRect();
	AstrumCircle circle = bCircle->GetCircle();

	float closestX = (std::max)(rect.LeftBottom.X, (std::min)(circle.Center.X, rect.RightTop.X));
	float closestY = (std::max)(rect.LeftBottom.Y, (std::min)(circle.Center.Y, rect.RightTop.Y));

	float dx = circle.Center.X - closestX;
	float dy = circle.Center.Y - closestY;

	return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
}

bool AstrumCollisionSystemSingleton::IsOverlapOBBToOBB(IAstrumOBBColliderComponent* aOBB, IAstrumOBBColliderComponent* bOBB) const {
	const auto axes1 = aOBB->GetAxes();
	const auto axes2 = bOBB->GetAxes();

	const auto rect1 = aOBB->GetRotatedRect();
	const auto rect2 = bOBB->GetRotatedRect();

	for (const auto& axis : { axes1.first, axes1.second, axes2.first, axes2.second }) {
		if (IsSeparatingAxis(rect1, rect2, axis)) {
			return false;
		}
	}

	return true;
}

bool AstrumCollisionSystemSingleton::IsOverlapAABBToOBB(IAstrumAABBColliderComponent* aAABB, IAstrumOBBColliderComponent* bOBB) const {
	const std::pair<AstrumVector2, AstrumVector2> axes2 = { {1.f,0.f},{0.f,1.f} };
	const auto axes1 = bOBB->GetAxes();

	const auto rect2 = static_cast<AstrumRotatedRect>(aAABB->GetRect());
	const auto rect1 = bOBB->GetRotatedRect();

	for (const auto& axis : { axes1.first, axes1.second, axes2.first, axes2.second }) {
		if (IsSeparatingAxis(rect1, rect2, axis)) {
			return false;
		}
	}

	return true;
}

bool AstrumCollisionSystemSingleton::IsOverlapCircleToOBB(IAstrumCircleColliderComponent* aCircle, IAstrumOBBColliderComponent* bOBB) const {
	const auto axes = bOBB->GetAxes();
	const auto centerRect = bOBB->GetCenterHalfRect();

	const AstrumCircle circle = aCircle->GetCircle();

	const AstrumVector2 diff = circle.Center - centerRect.Center;
	const float localX = diff.Dot(axes.first);
	const float localY = diff.Dot(axes.second);

	const float clampedX = (std::max)(-centerRect.HalfWidth, (std::min)(centerRect.HalfWidth, localX));
	const float clampedY = (std::max)(-centerRect.HalfHeight, (std::min)(centerRect.HalfHeight, localY));

	const float dx = localX - clampedX;
	const float dy = localY - clampedY;

	return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
}