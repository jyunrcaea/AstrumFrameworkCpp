#include "AstrumRenderQueue.hpp"

void AstrumRenderQueueSingleton::PeekToPreRender() {
	for (auto& renderable : renderQueue) {
		if (renderable) {
			renderable->PreRender();
		}
	}
}

void AstrumRenderQueueSingleton::DequeueToRender() {
	for(auto& renderable : renderQueue) {
		if (renderable) {
			renderable->Render();
		}
	}
	renderQueue.clear();
}

void AstrumRenderQueueSingleton::Dispose() {
	renderQueue.clear();
}