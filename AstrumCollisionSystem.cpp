#include "AstrumCollisionSystem.h"
#include "AstrumAABBColliderComponent.h"
#include "AstrumCircleColliderComponent.h"
#include "AstrumOBBColliderComponent.h"

void AstrumCollisionSystem::AddCollider(AstrumColliderComponent* const collider)
{
	if (!collider)
	{
		throw AstrumException("Cannot add a null collider to the collision system.");
	}
	colliders.push_back(collider);
}

bool AstrumCollisionSystem::RemoveCollider(AstrumColliderComponent* const collider)
{
	if (auto colliderIter = std::remove(colliders.begin(), colliders.end(), collider); colliderIter != colliders.end())
	{
		std::vector<std::pair< AstrumColliderComponent*, AstrumColliderComponent*>> removeTargets;
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

namespace {
	bool Overlap(AstrumColliderComponent* a, AstrumColliderComponent* b) {
		if (auto aabbA = dynamic_cast<AstrumAABBColliderComponent*>(a)) {
			if (auto aabbB = dynamic_cast<AstrumAABBColliderComponent*>(b)) return aabbA->IsOverlap(*aabbB);

			return false;
		}

		if (auto circleA = dynamic_cast<AstrumCircleColliderComponent*>(a)) {
			if (auto aabbB = dynamic_cast<AstrumAABBColliderComponent*>(b)) return circleA->IsOverlap(*aabbB);
			if (auto circleB = dynamic_cast<AstrumCircleColliderComponent*>(b)) return circleA->IsOverlap(*circleB);

			return false;
		}

		if (auto obbA = dynamic_cast<AstrumOBBColliderComponent*>(a)) {
			if (auto aabbB = dynamic_cast<AstrumAABBColliderComponent*>(b)) return obbA->IsOverlap(*aabbB);
			if (auto circleB = dynamic_cast<AstrumCircleColliderComponent*>(b)) return obbA->IsOverlap(*circleB);
			if (auto obbB = dynamic_cast<AstrumOBBColliderComponent*>(b)) return obbA->IsOverlap(*obbB);
			return false;
		}

		return false;
	}
}

void AstrumCollisionSystem::Update()
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

			bool result = Overlap(colliderX, colliderY);
			std::pair colliderPair = { colliderX, colliderY };
			bool over = collidedPairs.contains(colliderPair);

			if (result != over) {
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


		}
	}
}