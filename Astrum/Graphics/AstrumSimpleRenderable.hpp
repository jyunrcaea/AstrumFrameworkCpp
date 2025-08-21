#pragma once
#include <functional>
#include "IAstrumRenderable.hpp"

class AstrumSimpleRenderable : public IAstrumRenderable
{
public:
	AstrumSimpleRenderable(const std::function<void()>& preRender, const std::function<void()>& render)
		: preRenderFunction(preRender), renderFunction(render) {}
	AstrumSimpleRenderable(std::function<void()>&& preRender, std::function<void()>&& render)
		: preRenderFunction(std::move(preRender)), renderFunction(std::move(render)) {}

	virtual void PreRender() override { if (preRenderFunction) preRenderFunction(); }

protected:
	virtual void Render() override { if (renderFunction) renderFunction(); }

private:
	std::function<void()> preRenderFunction;
	std::function<void()> renderFunction;

public:
	static std::shared_ptr<AstrumSimpleRenderable> MakeShared(const std::function<void()>& preRender, const std::function<void()>& render) {
		return std::make_shared<AstrumSimpleRenderable>(preRender, render);
	}
	static std::shared_ptr<AstrumSimpleRenderable> MakeShared(std::function<void()>&& preRender, std::function<void()>&& render) {
		return std::make_shared<AstrumSimpleRenderable>(preRender, render);
	}
};