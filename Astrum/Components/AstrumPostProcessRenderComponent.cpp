#include "AstrumPostProcessRenderComponent.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumPostProcessRenderComponent::AstrumPostProcessRenderComponent(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer)
	: ConstantBuffer(constantBuffer) {}
AstrumPostProcessRenderComponent::AstrumPostProcessRenderComponent(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer)
	: ConstantBuffer(std::move(constantBuffer)) {}

void AstrumPostProcessRenderComponent::Render() {
	if (nullptr != ConstantBuffer) {
		ConstantBuffer->UpdateBuffer();
	}
	// 합성 결과는 화면 전체를 덮는 사각형이므로 깊이를 기록하면 이후에 그려지는 물체를 모두 가립니다.
	// 그리는 순서대로 겹쳐지도록 이 그리기에서만 깊이 기록을 끕니다.
	AstrumRenderer::Instance().SetDepthWriteEnabled(false);
	AstrumRenderMaterialComponent::Render();
	AstrumRenderer::Instance().SetDepthWriteEnabled(true);
}

IAstrumObject* AstrumPostProcessRenderComponent::GetOwner() const {
	static std::unique_ptr<IAstrumObject> origin = std::make_unique<AstrumObject>();
	return origin.get();
}
