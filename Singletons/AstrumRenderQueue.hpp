#pragma once
#include <queue>
#include <memory>
#include <algorithm>
#include "AstrumSingleton.hpp"
#include "AstrumRenderer.hpp"
#include "../Graphics/IAstrumRenderable.hpp"

struct IAstrumRenderable;

class AstrumRenderQueueSingleton : public AstrumSingleton<AstrumRenderQueueSingleton>
{
	friend class AstrumSingleton<AstrumRenderQueueSingleton>;
	friend class AstrumRenderQueue;

private:
	void Enqueue(const std::shared_ptr<IAstrumRenderable>& renderable);
	void Render();
	void Dispose();

private:
	std::queue<std::shared_ptr<IAstrumRenderable>> renderQueue;
};

class AstrumRenderQueue
{
public:
	// 렌더 큐에 그릴 객체를 삽입
	static void Enqueue(const std::shared_ptr<IAstrumRenderable>& renderable) {
		AstrumRenderQueueSingleton::Instance().Enqueue(renderable);
	}

private:
	friend class AstrumRenderer;
	static void Render() {
		AstrumRenderQueueSingleton::Instance().Render();
	}
	static void Dispose() {
		AstrumRenderQueueSingleton::Instance().Dispose();
	}
};