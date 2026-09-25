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
	// 충돌체를 제거합니다. invokeExitCallbacks가 true면 충돌 중이던 상대에게 OnCollisionExit를 호출합니다.
	bool RemoveCollider(AstrumColliderComponent* const collider, bool invokeExitCallbacks = true);
	void Update();
	// 해당 충돌체가 현재 충돌 시스템에 등록되어 있는지 확인합니다.
	bool IsRegistered(const AstrumColliderComponent* const collider) const;

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

	// 충돌 판정 루프가 끝난 뒤에 발생시킬 이벤트.
	// 콜백 안에서 충돌체/객체가 추가·제거되어도 판정 루프와 내부 상태가 깨지지 않도록, 이벤트는 모아서 나중에 호출합니다.
	struct PendingCollisionEvent {
		AstrumColliderComponent* First;
		AstrumColliderComponent* Second;
		bool IsEnter;
	};
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