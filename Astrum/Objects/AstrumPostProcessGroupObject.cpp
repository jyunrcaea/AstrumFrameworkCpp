#include "AstrumPostProcessGroupObject.hpp"
#include "../Singletons/AstrumWindow.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

AstrumPostProcessGroupObject::AstrumPostProcessGroupObject() {
	renderMaterialComponent->SetupRectangleMesh(
		AstrumWindow::GetWidth(),
		AstrumWindow::GetHeight()
	);
	bindRenderTarget = AstrumSimpleRenderable::MakeShared(
		nullptr,
		[this]() { this->renderTarget->Bind(); }
	);
	unbindRenderTarget = AstrumSimpleRenderable::MakeShared(
		nullptr,
		[this]() { this->renderTarget->Unbind(); renderMaterialComponent->Material = AstrumMaterial::MakeShared(renderTarget->GetTexture()); }
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