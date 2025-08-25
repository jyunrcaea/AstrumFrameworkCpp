#include "AstrumConstantBufferComponent.hpp"

AstrumConstantBufferComponent::AstrumConstantBufferComponent() {}
AstrumConstantBufferComponent::AstrumConstantBufferComponent(const std::shared_ptr<IAstrumConstantBuffer>& buffer)
	: ConstantBuffer(buffer) { }
AstrumConstantBufferComponent::AstrumConstantBufferComponent(std::shared_ptr<IAstrumConstantBuffer>&& buffer)
	: ConstantBuffer(std::move(buffer)) {}

void AstrumConstantBufferComponent::Draw() {
	if (ConstantBuffer) ConstantBuffer->UpdateBuffer();
}
