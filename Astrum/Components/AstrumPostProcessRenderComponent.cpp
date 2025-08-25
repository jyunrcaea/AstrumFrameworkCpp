#include "AstrumPostProcessRenderComponent.hpp"

AstrumPostProcessRenderComponent::AstrumPostProcessRenderComponent(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer)
	: ConstantBuffer(constantBuffer) {}
AstrumPostProcessRenderComponent::AstrumPostProcessRenderComponent(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer)
	: ConstantBuffer(std::move(constantBuffer)) {}

void AstrumPostProcessRenderComponent::Render() {
	if (nullptr != ConstantBuffer) {
		ConstantBuffer->UpdateBuffer();
	}
	AstrumRenderMaterialComponent::Render();
}

IAstrumObject* AstrumPostProcessRenderComponent::GetOwner() const {
	static std::unique_ptr<IAstrumObject> origin = std::make_unique<AstrumObject>();
	return origin.get();
}
