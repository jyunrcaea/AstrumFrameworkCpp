#include "AstrumRenderQueue.hpp"

namespace Astrum {
	void RenderQueueSingleton::PeekToPreRender() {
		for (auto& renderable : renderQueue) {
			if (renderable) {
				renderable->PreRender();
			}
		}
	}

	void RenderQueueSingleton::DequeueToRender() {
		for (auto& renderable : renderQueue) {
			if (renderable) {
				renderable->Render();
			}
		}
		renderQueue.clear();
	}

	void RenderQueueSingleton::Dispose() {
		renderQueue.clear();
	}
}