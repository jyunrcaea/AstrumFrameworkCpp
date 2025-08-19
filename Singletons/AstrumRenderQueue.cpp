#include "AstrumRenderQueue.hpp"

void AstrumRenderQueueSingleton::Enqueue(const std::shared_ptr<IAstrumRenderable>& renderable) {
	if (nullptr != renderable) {
		renderQueue.emplace(renderable);
	}
}

void AstrumRenderQueueSingleton::Enqueue(std::shared_ptr<IAstrumRenderable>&& renderable) {
	if (nullptr != renderable) {
		renderQueue.emplace(std::move(renderable));
	}
}

void AstrumRenderQueueSingleton::PeekToPreRender() {
	for(int remain=renderQueue.size(); remain > 0; remain--) {
		renderQueue.front()->PreRender();
		renderQueue.emplace(std::move(renderQueue.front()));
		renderQueue.pop();
	}
}

void AstrumRenderQueueSingleton::DequeueToRender() {
	while (false == renderQueue.empty()) {
		renderQueue.front()->Render();
		renderQueue.pop();
	}
}

void AstrumRenderQueueSingleton::Dispose() {
	while (false == renderQueue.empty()) {
		renderQueue.pop();
	}
}