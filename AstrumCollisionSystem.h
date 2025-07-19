#pragma once
#include <vector>
#include <unordered_set>
#include <set>
#include <memory>
#include "AstrumColliderComponent.h"
#include "Singleton.hpp"
#include "AstrumException.hpp"
#include "AstrumObject.hpp"

class AstrumColliderComponent;

class AstrumCollisionSystem : public Singleton<AstrumCollisionSystem>
{
	friend class Singleton<AstrumCollisionSystem>;

public:
	void AddCollider(AstrumColliderComponent* const collider);
	bool RemoveCollider(AstrumColliderComponent* const collider);
	void Update();

private:
	// Component is referenced by object, so need not use a shared_ptr
	std::vector<AstrumColliderComponent*> colliders;
	std::set<std::pair<AstrumColliderComponent*, AstrumColliderComponent*>> collidedPairs;
};

