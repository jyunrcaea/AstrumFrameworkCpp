#pragma once
#include <vector>
#include <unordered_set>
#include <set>
#include <memory>
#include "AstrumSingleton.hpp"
#include "../Components/AstrumColliderComponent.hpp"
#include "../Components/IAstrumAABBColliderComponent.hpp"
#include "../Components/IAstrumCircleColliderComponent.hpp"
#include "../Components/IAstrumOBBColliderComponent.hpp"

class AstrumColliderComponent;

class AstrumCollisionSystemSingleton : public AstrumSingleton<AstrumCollisionSystemSingleton>
{
	friend class AstrumSingleton<AstrumCollisionSystemSingleton>;
	friend class AstrumCollisionSystem;
	AstrumCollisionSystemSingleton();

public:
	void AddCollider(AstrumColliderComponent* const collider);
	bool RemoveCollider(AstrumColliderComponent* const collider);
	void Update();

private:
	bool IsOverlapAABBToAABB(IAstrumAABBColliderComponent* aAABB, IAstrumAABBColliderComponent* bAABB) const;
	bool IsOverlapCircleToCircle(IAstrumCircleColliderComponent* aCircle, IAstrumCircleColliderComponent* bCircle) const;
	bool IsOverlapAABBToCircle(IAstrumAABBColliderComponent* aAABB, IAstrumCircleColliderComponent* bCircle) const;
	bool IsOverlapAABBToOBB(IAstrumAABBColliderComponent* aAABB, IAstrumOBBColliderComponent* bOBB) const;
	bool IsOverlapCircleToOBB(IAstrumCircleColliderComponent* aCircle, IAstrumOBBColliderComponent* bOBB) const;
	bool IsOverlapOBBToOBB(IAstrumOBBColliderComponent* aOBB, IAstrumOBBColliderComponent* bOBB) const;

private:
	// Component is referenced by object, so need not use a shared_ptr
	std::vector<AstrumColliderComponent*> colliders;
	std::set<std::pair<AstrumColliderComponent*, AstrumColliderComponent*>> collidedPairs;
};

class AstrumCollisionSystem {
	AstrumCollisionSystem() = delete;
public:
	inline static bool IsOverlapAABBToAABB(IAstrumAABBColliderComponent* aAABB, IAstrumAABBColliderComponent* bAABB) { 
		return AstrumCollisionSystemSingleton::Instance().IsOverlapAABBToAABB(aAABB, bAABB);
	}
	inline static bool IsOverlapCircleToCircle(IAstrumCircleColliderComponent* aCircle, IAstrumCircleColliderComponent* bCircle) { 
		return AstrumCollisionSystemSingleton::Instance().IsOverlapCircleToCircle(aCircle, bCircle);
	}
	inline static bool IsOverlapAABBToCircle(IAstrumAABBColliderComponent* aAABB, IAstrumCircleColliderComponent* bCircle) { 
		return AstrumCollisionSystemSingleton::Instance().IsOverlapAABBToCircle(aAABB, bCircle);
	}
	inline static bool IsOverlapAABBToOBB(IAstrumAABBColliderComponent* aAABB, IAstrumOBBColliderComponent* bOBB) { 
		return AstrumCollisionSystemSingleton::Instance().IsOverlapAABBToOBB(aAABB, bOBB);
	}
	inline static bool IsOverlapCircleToOBB(IAstrumCircleColliderComponent* aCircle, IAstrumOBBColliderComponent* bOBB) { 
		return AstrumCollisionSystemSingleton::Instance().IsOverlapCircleToOBB(aCircle, bOBB); 
	}
	inline static bool IsOverlapOBBToOBB(IAstrumOBBColliderComponent* aOBB, IAstrumOBBColliderComponent* bOBB) {
		return AstrumCollisionSystemSingleton::Instance().IsOverlapOBBToOBB(aOBB, bOBB); 
	}
};