#include "AstrumRenderQueue.hpp"

void AstrumRenderQueueSingleton::Enqueue(const std::shared_ptr<IAstrumRenderable>& renderable) {
	if (nullptr != renderable) {
		renderQueue.push(renderable);
	}
}

void AstrumRenderQueueSingleton::Render() {
	while (false == renderQueue.empty()) {
		renderQueue.front()->PreRender();
		renderQueue.pop();
	}
}

void AstrumRenderQueueSingleton::Dispose() {
	while (false == renderQueue.empty()) {
		renderQueue.pop();
	}
}