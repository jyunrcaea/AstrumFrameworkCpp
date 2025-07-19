#include "AstrumComponent.h"

void AstrumComponent::Prepare() { }
void AstrumComponent::Update() { }
void AstrumComponent::Release() { }

void AstrumComponent::SetOwner(IAstrumObject* const obj)
{
	this->owner = obj;
}

IAstrumObject* AstrumComponent::GetOwner() const
{
	return owner;
}
