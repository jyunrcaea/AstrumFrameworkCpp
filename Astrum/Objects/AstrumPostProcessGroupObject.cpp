#include "AstrumPostProcessGroupObject.hpp"
#include "../Singletons/AstrumWindow.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Singletons/AstrumRenderer.hpp"

AstrumPostProcessGroupObject::AstrumPostProcessGroupObject() {
	renderMaterialComponent->Material = AstrumMaterial::MakeShared(renderTarget);
	renderMaterialComponent->SetupMeshFromTexture();
	bindRenderTarget = AstrumSimpleRenderable::MakeShared(
		nullptr,
		[this]() { 
			this->renderTarget->Bind();
			this->renderTarget->Clear();
		}
	);
	unbindRenderTarget = AstrumSimpleRenderable::MakeShared(
		nullptr,
		[this]() { this->renderTarget->Unbind(); }
	);
}

void AstrumPostProcessGroupObject::Draw() {
	AstrumRenderQueue::Enqueue(bindRenderTarget);
	AstrumGroupObject::Draw();
	AstrumRenderQueue::Enqueue(unbindRenderTarget);
	AstrumRenderQueue::Enqueue(renderMaterialComponent);
}

std::shared_ptr<IAstrumShaderSetup> AstrumPostProcessGroupObject::GetCustomShaderPipeline() const {
	return renderMaterialComponent->GetCustomShaderPipeline();
}
void AstrumPostProcessGroupObject::SetCustomShaderPipeline(const std::shared_ptr<IAstrumShaderSetup>& customShaderPipeline) {
	renderMaterialComponent->SetCustomShaderPipeline(customShaderPipeline);
}