#include "AstrumCollisionSystem.hpp"
#include <algorithm>
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
		AstrumException("Cannot add a null collider to the collision system.").Alert();
		return;
	}
	// Prepare()가 여러번 호출되어도 중복 등록되지 않도록 합니다.
	if (IsRegistered(collider)) return;
	colliders.push_back(collider);
}

bool AstrumCollisionSystemSingleton::RemoveCollider(AstrumColliderComponent* const collider, bool invokeExitCallbacks)
{
	auto colliderIter = std::find(colliders.begin(), colliders.end(), collider);
	if (colliderIter == colliders.end()) return false;
	colliders.erase(colliderIter);

	// 1. 내부 상태(쌍 목록)를 먼저 정리하고,
	std::vector<AstrumColliderComponent*> partners;
	for (auto it = collidedPairs.begin(); it != collidedPairs.end();)
	{
		if (it->first == collider) partners.push_back(it->second);
		else if (it->second == collider) partners.push_back(it->first);
		else { ++it; continue; }
		it = collidedPairs.erase(it);
	}

	if (false == invokeExitCallbacks) return true;

	// 2. 상태가 일관된 뒤에 콜백을 호출합니다. (콜백 안에서 다른 충돌체가 제거될 수 있으므로 매번 등록 여부를 확인)
	for (auto* const partner : partners)
	{
		if (IsRegistered(partner)) partner->InvokeOnCollisionExit(collider);
	}
	return true;
}

bool AstrumCollisionSystemSingleton::IsRegistered(const AstrumColliderComponent* const collider) const
{
	return std::find(colliders.begin(), colliders.end(), collider) != colliders.end();
}

void AstrumCollisionSystemSingleton::Update()
{
	std::vector<PendingCollisionEvent> events;

	// 1. 판정: 콜백을 호출하지 않고 충돌 상태 변화만 기록합니다.
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
				if (result) collidedPairs.insert(colliderPair);
				else collidedPairs.erase(colliderPair);
				events.push_back({ colliderX, colliderY, result });
			}
			//for end.
		}
	}

	// 2. 발생: 콜백에서 충돌체가 제거(해제)되었을 수 있으므로, 호출 직전마다 등록 여부를 확인합니다.
	// (제거된 충돌체는 RemoveCollider()에서 상대에게 Exit 이벤트를 이미 전달했습니다.)
	for (const auto& event : events)
	{
		if (false == IsRegistered(event.First) || false == IsRegistered(event.Second)) continue;
		if (event.IsEnter) event.First->InvokeOnCollisionEnter(event.Second);
		else event.First->InvokeOnCollisionExit(event.Second);

		if (false == IsRegistered(event.First) || false == IsRegistered(event.Second)) continue;
		if (event.IsEnter) event.Second->InvokeOnCollisionEnter(event.First);
		else event.Second->InvokeOnCollisionExit(event.First);
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