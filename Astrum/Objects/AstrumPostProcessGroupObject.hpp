#pragma once
#include <memory>
#include "AstrumGroupObject.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Graphics/AstrumSimpleRenderable.hpp"

class AstrumPostProcessGroupObject : public AstrumGroupObject
{
public:
	AstrumPostProcessGroupObject();

	virtual void Draw() override;

	std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const;
	void SetCustomShaderPipeline(const std::shared_ptr<IAstrumShaderSetup>& customShaderPipeline);

private:
	std::shared_ptr<AstrumRenderTarget> renderTarget = AstrumRenderTarget::MakeShared(AstrumWindow::GetWidth(), AstrumWindow::GetHeight());
	std::shared_ptr<AstrumRenderMaterialComponent> renderMaterialComponent = AstrumRenderMaterialComponent::MakeShared();

	std::shared_ptr<AstrumSimpleRenderable> bindRenderTarget = nullptr;
	std::shared_ptr<AstrumSimpleRenderable> unbindRenderTarget = nullptr;
};