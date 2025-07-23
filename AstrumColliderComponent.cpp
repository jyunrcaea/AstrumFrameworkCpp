#include "AstrumColliderComponent.h"

//AstrumColliderComponent::AstrumColliderComponent(IAstrumObject* owner)
//{
//	if (owner == nullptr)
//	{
//		throw AstrumException("Owner cannot be null.");
//	}
//
//	SetOwner(owner);
//}

AstrumColliderComponent::AstrumColliderComponent()
{
}

void AstrumColliderComponent::Prepare()
{
	AstrumComponent::Prepare();
	AstrumCollisionSystem::Instance().AddCollider(this);
}

void AstrumColliderComponent::Release()
{
	AstrumCollisionSystem::Instance().RemoveCollider(this);
	AstrumComponent::Release();
}

void AstrumColliderComponent::InvokeOnCollisionEnter(AstrumColliderComponent* const other) { if (onCollisionEnter) onCollisionEnter(other); }
void AstrumColliderComponent::InvokeOnCollisionExit(AstrumColliderComponent* const other) { if (onCollisionExit) onCollisionExit(other); }

AstrumColliderType AstrumColliderComponent::GetColliderType() const { return AstrumColliderType::AstrumColliderType_None; }
void AstrumColliderComponent::SetOwner(IAstrumObject* const obj) { AstrumComponent::SetOwner(obj); }