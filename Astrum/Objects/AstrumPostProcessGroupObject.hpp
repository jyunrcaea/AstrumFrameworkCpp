#pragma once
#include <memory>
#include "AstrumGroupObject.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "../Components/AstrumRenderMaterialComponent.hpp"
#include "../Graphics/AstrumSimpleRenderable.hpp"

namespace Astrum
{
	class PostProcessGroupObject : public GroupObject
	{
		class PostProcessRenderComponent : public RenderMaterialComponent
		{
		public:
			virtual IObject* GetOwner() const override {
				static std::unique_ptr<IObject> origin = std::make_unique<Object>();
				return origin.get();
			}
		};

	public:
		PostProcessGroupObject();

		virtual void Draw() override;

		std::shared_ptr<IShaderSetup> GetCustomShaderPipeline() const;
		void SetCustomShaderPipeline(const std::shared_ptr<IShaderSetup>& customShaderPipeline) { renderMaterialComponent->SetCustomShaderPipeline(customShaderPipeline); }
		void SetCustomShaderPipeline(std::shared_ptr<IShaderSetup>&& customShaderPipeline) { renderMaterialComponent->SetCustomShaderPipeline(std::move(customShaderPipeline)); }

	private:
		std::shared_ptr<RenderTarget> renderTarget = RenderTarget::MakeShared(Window::GetWidth(), Window::GetHeight());
		std::shared_ptr<PostProcessRenderComponent> renderMaterialComponent = std::make_shared<PostProcessRenderComponent>();

		std::shared_ptr<SimpleRenderable> bindRenderTarget = nullptr;
		std::shared_ptr<SimpleRenderable> unbindRenderTarget = nullptr;
	};
}