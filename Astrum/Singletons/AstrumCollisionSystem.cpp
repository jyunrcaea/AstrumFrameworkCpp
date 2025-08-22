#include "AstrumCollisionSystem.hpp"
#include "../Vectors/AstrumVector2.hpp"
#include "../AstrumException.hpp"

namespace Astrum
{
	namespace {
		std::pair<float, float> GetProjection(const Vector2& axis, const RotatedRect& rect) {
			float min = std::numeric_limits<float>::max();
			float max = std::numeric_limits<float>::lowest();
			for (const auto& point : { rect.LeftBottom, rect.RightBottom, rect.RightTop, rect.LeftTop }) {
				float projection = point.Dot(axis);
				min = (std::min)(min, projection);
				max = (std::max)(max, projection);
			}
			return { min, max };
		}

		bool IsSeparatingAxis(const RotatedRect& a, const RotatedRect& b, Vector2 axis) {
			auto obb1 = GetProjection(axis, a);
			auto obb2 = GetProjection(axis, b);

			return obb1.second < obb2.first || obb2.second < obb1.first;
		}
	}

	CollisionSystemSingleton::CollisionSystemSingleton() {}

	void CollisionSystemSingleton::AddCollider(ColliderComponent* const collider)
	{
		if (!collider)
		{
			throw Exception("Cannot add a null collider to the collision system.");
		}
		colliders.push_back(collider);
	}

	bool CollisionSystemSingleton::RemoveCollider(ColliderComponent* const collider)
	{
		if (auto colliderIter = std::remove(colliders.begin(), colliders.end(), collider); colliderIter != colliders.end())
		{
			std::vector<std::pair<ColliderComponent*, ColliderComponent*>> removeTargets;
			for (auto& pair : collidedPairs)
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

	void CollisionSystemSingleton::Update()
	{
		for (size_t x = 0; x < colliders.size(); x++)
		{
			for (size_t y = x + 1; y < colliders.size(); y++)
			{
				ColliderComponent* colliderX = colliders[x];
				ColliderComponent* colliderY = colliders[y];

				int colliderTypeX = colliderX->GetColliderType();
				int colliderTypeY = colliderY->GetColliderType();

				if (colliderTypeX == EColliderType::None || colliderTypeY == EColliderType::None)
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

	bool CollisionSystemSingleton::IsOverlapAABBToAABB(IAABBColliderComponent* aAABB, IAABBColliderComponent* bAABB) const {
		auto a = aAABB->GetRect();
		auto b = bAABB->GetRect();
		float w = std::min(a.RightTop.X, b.RightTop.X) - std::max(a.LeftBottom.X, b.LeftBottom.X);
		float h = std::min(a.RightTop.Y, b.RightTop.Y) - std::max(a.LeftBottom.Y, b.LeftBottom.Y);
		return w >= 0 && h >= 0;
	}

	bool CollisionSystemSingleton::IsOverlapCircleToCircle(ICircleColliderComponent* aCircle, ICircleColliderComponent* bCircle) const {
		auto a = aCircle->GetCircle();
		auto b = bCircle->GetCircle();

		return a.Center.Distance(b.Center) <= (a.Radius + b.Radius);
	}

	bool CollisionSystemSingleton::IsOverlapAABBToCircle(IAABBColliderComponent* aAABB, ICircleColliderComponent* bCircle) const {
		Rect rect = aAABB->GetRect();
		Circle circle = bCircle->GetCircle();

		float closestX = std::max(rect.LeftBottom.X, std::min(circle.Center.X, rect.RightTop.X));
		float closestY = std::max(rect.LeftBottom.Y, std::min(circle.Center.Y, rect.RightTop.Y));

		float dx = circle.Center.X - closestX;
		float dy = circle.Center.Y - closestY;

		return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
	}

	bool CollisionSystemSingleton::IsOverlapOBBToOBB(IOBBColliderComponent* aOBB, IOBBColliderComponent* bOBB) const {
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

	bool CollisionSystemSingleton::IsOverlapAABBToOBB(IAABBColliderComponent* aAABB, IOBBColliderComponent* bOBB) const {
		const std::pair<Vector2, Vector2> axes2 = { {1.f,0.f},{0.f,1.f} };
		const auto axes1 = bOBB->GetAxes();

		const auto rect2 = static_cast<RotatedRect>(aAABB->GetRect());
		const auto rect1 = bOBB->GetRotatedRect();

		for (const auto& axis : { axes1.first, axes1.second, axes2.first, axes2.second }) {
			if (IsSeparatingAxis(rect1, rect2, axis)) {
				return false;
			}
		}

		return true;
	}

	bool CollisionSystemSingleton::IsOverlapCircleToOBB(ICircleColliderComponent* aCircle, IOBBColliderComponent* bOBB) const {
		const auto axes = bOBB->GetAxes();
		const auto centerRect = bOBB->GetCenterHalfRect();

		const Circle circle = aCircle->GetCircle();

		const Vector2 diff = circle.Center - centerRect.Center;
		const float localX = diff.Dot(axes.first);
		const float localY = diff.Dot(axes.second);

		const float clampedX = std::max(-centerRect.HalfWidth, std::min(centerRect.HalfWidth, localX));
		const float clampedY = std::max(-centerRect.HalfHeight, std::min(centerRect.HalfHeight, localY));

		const float dx = localX - clampedX;
		const float dy = localY - clampedY;

		return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
	}
}