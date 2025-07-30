#include "AstrumStateComponent.hpp"

void AstrumStateComponent::Prepare() {
	AstrumComponent::Prepare();
}

void AstrumStateComponent::Update() {
	if (nullptr == statusGraph) return;



	AstrumComponent::Update();
}

void AstrumStateComponent::Release() {
	AstrumComponent::Release();
}