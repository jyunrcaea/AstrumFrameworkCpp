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

namespace Astrum
{
	class ColliderComponent;

	class CollisionSystemSingleton : public Singleton<CollisionSystemSingleton>
	{
		friend class Singleton<CollisionSystemSingleton>;
		friend class CollisionSystem;
		CollisionSystemSingleton();

	public:
		void AddCollider(ColliderComponent* const collider);
		bool RemoveCollider(ColliderComponent* const collider);
		void Update();

	private:
		bool IsOverlapAABBToAABB(IAABBColliderComponent* aAABB, IAABBColliderComponent* bAABB) const;
		bool IsOverlapCircleToCircle(ICircleColliderComponent* aCircle, ICircleColliderComponent* bCircle) const;
		bool IsOverlapAABBToCircle(IAABBColliderComponent* aAABB, ICircleColliderComponent* bCircle) const;
		bool IsOverlapAABBToOBB(IAABBColliderComponent* aAABB, IOBBColliderComponent* bOBB) const;
		bool IsOverlapCircleToOBB(ICircleColliderComponent* aCircle, IOBBColliderComponent* bOBB) const;
		bool IsOverlapOBBToOBB(IOBBColliderComponent* aOBB, IOBBColliderComponent* bOBB) const;

	private:
		// Component is referenced by object, so need not use a shared_ptr
		std::vector<ColliderComponent*> colliders;
		std::set<std::pair<ColliderComponent*, ColliderComponent*>> collidedPairs;
	};

	class CollisionSystem {
		CollisionSystem() = delete;
	public:
		inline static bool IsOverlapAABBToAABB(IAABBColliderComponent* aAABB, IAABBColliderComponent* bAABB) {
			return CollisionSystemSingleton::Instance().IsOverlapAABBToAABB(aAABB, bAABB);
		}
		inline static bool IsOverlapCircleToCircle(ICircleColliderComponent* aCircle, ICircleColliderComponent* bCircle) {
			return CollisionSystemSingleton::Instance().IsOverlapCircleToCircle(aCircle, bCircle);
		}
		inline static bool IsOverlapAABBToCircle(IAABBColliderComponent* aAABB, ICircleColliderComponent* bCircle) {
			return CollisionSystemSingleton::Instance().IsOverlapAABBToCircle(aAABB, bCircle);
		}
		inline static bool IsOverlapAABBToOBB(IAABBColliderComponent* aAABB, IOBBColliderComponent* bOBB) {
			return CollisionSystemSingleton::Instance().IsOverlapAABBToOBB(aAABB, bOBB);
		}
		inline static bool IsOverlapCircleToOBB(ICircleColliderComponent* aCircle, IOBBColliderComponent* bOBB) {
			return CollisionSystemSingleton::Instance().IsOverlapCircleToOBB(aCircle, bOBB);
		}
		inline static bool IsOverlapOBBToOBB(IOBBColliderComponent* aOBB, IOBBColliderComponent* bOBB) {
			return CollisionSystemSingleton::Instance().IsOverlapOBBToOBB(aOBB, bOBB);
		}
	};
}