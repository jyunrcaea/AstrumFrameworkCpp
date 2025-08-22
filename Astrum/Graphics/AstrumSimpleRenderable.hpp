#pragma once
#include <functional>
#include "IAstrumRenderable.hpp"

namespace Astrum
{
	class SimpleRenderable : public IRenderable
	{
	public:
		SimpleRenderable(const std::function<void()>& preRender, const std::function<void()>& render)
			: preRenderFunction(preRender), renderFunction(render) {}
		SimpleRenderable(std::function<void()>&& preRender, std::function<void()>&& render)
			: preRenderFunction(std::move(preRender)), renderFunction(std::move(render)) {}

		virtual void PreRender() override { if (preRenderFunction) preRenderFunction(); }

	protected:
		virtual void Render() override { if (renderFunction) renderFunction(); }

	private:
		std::function<void()> preRenderFunction;
		std::function<void()> renderFunction;

	public:
		static std::shared_ptr<SimpleRenderable> MakeShared(const std::function<void()>& preRender, const std::function<void()>& render) {
			return std::make_shared<SimpleRenderable>(preRender, render);
		}
		static std::shared_ptr<SimpleRenderable> MakeShared(std::function<void()>&& preRender, std::function<void()>&& render) {
			return std::make_shared<SimpleRenderable>(std::move(preRender), std::move(render));
		}
	};
}