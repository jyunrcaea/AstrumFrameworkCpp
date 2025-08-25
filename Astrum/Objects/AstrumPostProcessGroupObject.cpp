#include "AstrumPostProcessGroupObject.hpp"
#include "../Singletons/AstrumWindow.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumPostProcessGroupObject::AstrumPostProcessGroupObject() {
	bindRenderTarget = AstrumSimpleRenderable::MakeShared(
		nullptr,
		[this]() { 
			this->renderTarget->Bind();
			this->renderTarget->Clear();
		}
	);
	unbindRenderTarget = AstrumSimpleRenderable::MakeShared(
		nullptr,
		[this]() { 
			this->renderTarget->Unbind(); 
		}
	);
	renderComponent->Material = AstrumMaterial::MakeShared(renderTarget);
	renderComponent->SetupMeshFromTexture();
}
AstrumPostProcessGroupObject::AstrumPostProcessGroupObject(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer)
	: AstrumPostProcessGroupObject() {
	renderComponent->ConstantBuffer = constantBuffer;
}
AstrumPostProcessGroupObject::AstrumPostProcessGroupObject(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer)
	: AstrumPostProcessGroupObject() {
	renderComponent->ConstantBuffer = std::move(constantBuffer);
}

void AstrumPostProcessGroupObject::Draw() {
	AstrumRenderQueue::Enqueue(bindRenderTarget);
	AstrumGroupObject::Draw();
	AstrumRenderQueue::Enqueue(unbindRenderTarget);
	AstrumRenderQueue::Enqueue(renderComponent);
}

std::shared_ptr<IAstrumShaderSetup> AstrumPostProcessGroupObject::GetCustomShaderPipeline() const {
	return renderComponent->GetCustomShaderPipeline();
}