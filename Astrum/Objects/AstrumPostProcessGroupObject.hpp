#pragma once
#include <memory>
#include "AstrumGroupObject.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Graphics/AstrumSimpleRenderable.hpp"

class AstrumPostProcessGroupObject : public AstrumGroupObject
{
	class PostProcessRenderComponent : public AstrumRenderMaterialComponent
	{
	public:
		virtual IAstrumObject* GetOwner() const override {
			static std::unique_ptr<IAstrumObject> origin = std::make_unique<AstrumObject>();
			return origin.get();
		}
	};

public:
	AstrumPostProcessGroupObject();

	virtual void Draw() override;

	std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const;
	void SetCustomShaderPipeline(const std::shared_ptr<IAstrumShaderSetup>& customShaderPipeline) { renderMaterialComponent->SetCustomShaderPipeline(customShaderPipeline); }
	void SetCustomShaderPipeline(std::shared_ptr<IAstrumShaderSetup>&& customShaderPipeline) { renderMaterialComponent->SetCustomShaderPipeline(std::move(customShaderPipeline)); }

private:
	std::shared_ptr<AstrumRenderTarget> renderTarget = AstrumRenderTarget::MakeShared(AstrumWindow::GetWidth(), AstrumWindow::GetHeight());
	std::shared_ptr<PostProcessRenderComponent> renderMaterialComponent = std::make_shared<PostProcessRenderComponent>();

	std::shared_ptr<AstrumSimpleRenderable> bindRenderTarget = nullptr;
	std::shared_ptr<AstrumSimpleRenderable> unbindRenderTarget = nullptr;
};