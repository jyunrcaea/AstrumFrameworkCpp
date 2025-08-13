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
	void Enqueue(std::shared_ptr<IAstrumRenderable>&& renderable);
	void PeekToPreRender();
	void DequeueToRender();
	void Dispose();

private:
	std::queue<std::shared_ptr<IAstrumRenderable>> renderQueue;
};

class AstrumRenderQueue
{
public:
	// 렌더 큐에 그릴 객체를 삽입
	static void Enqueue(const std::shared_ptr<IAstrumRenderable>& renderable) { AstrumRenderQueueSingleton::Instance().Enqueue(renderable); }
	static void Enqueue(std::shared_ptr<IAstrumRenderable>&& renderable) { AstrumRenderQueueSingleton::Instance().Enqueue(renderable); }
private:
	friend class AstrumRenderer;
	static void PeekToPreRender() { AstrumRenderQueueSingleton::Instance().PeekToPreRender(); }
	static void DequeueToRender() { AstrumRenderQueueSingleton::Instance().DequeueToRender(); }
	static void Dispose() { AstrumRenderQueueSingleton::Instance().Dispose(); }
};