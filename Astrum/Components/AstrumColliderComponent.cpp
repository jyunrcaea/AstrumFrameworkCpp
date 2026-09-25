#include "AstrumColliderComponent.hpp"

AstrumColliderComponent::AstrumColliderComponent() { }

AstrumColliderComponent::~AstrumColliderComponent()
{
	if (registered) {
		// 소멸 중인 객체(파생 부분은 이미 소멸됨)를 콜백에 넘기지 않도록, 상대에게 Exit 이벤트는 보내지 않습니다.
		AstrumCollisionSystemSingleton::Instance().RemoveCollider(this, false);
	}
}

void AstrumColliderComponent::Prepare()
{
	AstrumComponent::Prepare();
	AstrumCollisionSystemSingleton::Instance().AddCollider(this);
	registered = true;
}

void AstrumColliderComponent::Release()
{
	AstrumCollisionSystemSingleton::Instance().RemoveCollider(this);
	registered = false;
	AstrumComponent::Release();
}

void AstrumColliderComponent::InvokeOnCollisionEnter(AstrumColliderComponent* const other) {
	if ((other->OwnBitmask & ReceiveBitmask) == 0) return;
	if (onCollisionEnter) onCollisionEnter(other);
}
void AstrumColliderComponent::InvokeOnCollisionExit(AstrumColliderComponent* const other) {
	if ((other->OwnBitmask & ReceiveBitmask) == 0) return;
	if (onCollisionExit) onCollisionExit(other);
}

void AstrumColliderComponent::SetOwner(IAstrumObject* const obj) { AstrumComponent::SetOwner(obj); }