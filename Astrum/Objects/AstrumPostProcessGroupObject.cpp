#include "AstrumPostProcessGroupObject.hpp"
#include "../Singletons/AstrumWindow.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"
#include "../Singletons/AstrumRenderer.hpp"

namespace Astrum
{
	PostProcessGroupObject::PostProcessGroupObject() {
		renderMaterialComponent->Material = Material::MakeShared(renderTarget);
		renderMaterialComponent->SetupMeshFromTexture();
		bindRenderTarget = SimpleRenderable::MakeShared(
			nullptr,
			[this]() {
				this->renderTarget->Bind();
				this->renderTarget->Clear();
			}
		);
		unbindRenderTarget = SimpleRenderable::MakeShared(
			nullptr,
			[this]() {
				this->renderTarget->Unbind();
			}
		);
	}

	void PostProcessGroupObject::Draw() {
		RenderQueue::Enqueue(bindRenderTarget);
		GroupObject::Draw();
		RenderQueue::Enqueue(unbindRenderTarget);
		RenderQueue::Enqueue(renderMaterialComponent);
	}

	std::shared_ptr<IShaderSetup> PostProcessGroupObject::GetCustomShaderPipeline() const {
		return renderMaterialComponent->GetCustomShaderPipeline();
	}
}