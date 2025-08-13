#include "AstrumConstantBufferComponent.hpp"

AstrumConstantBufferComponent::AstrumConstantBufferComponent(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer)
	: ConstantBuffer(constantBuffer) { }

void AstrumConstantBufferComponent::PreRender() {
	if (ConstantBuffer) ConstantBuffer->UpdateBuffer();
}
