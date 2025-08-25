#pragma once
#include <memory>
#include "AstrumGroupObject.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "../Components/AstrumPostProcessRenderComponent.hpp"
#include "../Graphics/AstrumSimpleRenderable.hpp"

class AstrumPostProcessGroupObject : public AstrumGroupObject
{
public:
	AstrumPostProcessGroupObject();
	AstrumPostProcessGroupObject(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer);
	AstrumPostProcessGroupObject(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer);

	virtual void Draw() override;

	std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const;
	void SetCustomShaderPipeline(const std::shared_ptr<IAstrumShaderSetup>& customShaderPipeline) { renderComponent->SetCustomShaderPipeline(customShaderPipeline); }
	void SetCustomShaderPipeline(std::shared_ptr<IAstrumShaderSetup>&& customShaderPipeline) { renderComponent->SetCustomShaderPipeline(std::move(customShaderPipeline)); }

	std::shared_ptr<IAstrumConstantBuffer> GetConstantBuffer() const { return renderComponent->ConstantBuffer; }
	void SetConstantBuffer(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer) { renderComponent->ConstantBuffer = constantBuffer; }
	void SetConstantBuffer(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer) { renderComponent->ConstantBuffer = std::move(constantBuffer); }
private:
	std::shared_ptr<AstrumRenderTarget> renderTarget = AstrumRenderTarget::MakeShared(AstrumWindow::GetWidth(), AstrumWindow::GetHeight());
	std::shared_ptr<AstrumPostProcessRenderComponent> renderComponent = AstrumPostProcessRenderComponent::MakeShared();

	std::shared_ptr<AstrumSimpleRenderable> bindRenderTarget = nullptr;
	std::shared_ptr<AstrumSimpleRenderable> unbindRenderTarget = nullptr;
};