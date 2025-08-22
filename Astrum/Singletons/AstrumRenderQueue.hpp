#pragma once
#include <queue>
#include <memory>
#include <algorithm>
#include "AstrumSingleton.hpp"
#include "AstrumRenderer.hpp"
#include "../Graphics/IAstrumRenderable.hpp"

namespace Astrum {
	struct IRenderable;
	class RenderQueue;

	class RenderQueueSingleton : public Singleton<RenderQueueSingleton>
	{
		friend class Singleton<RenderQueueSingleton>;
		friend class RenderQueue;

	private:
		void Enqueue(const std::shared_ptr<IRenderable>& renderable) {
			if (nullptr != renderable) {
				renderQueue.emplace_back(renderable);
			}
		}
		void Enqueue(std::shared_ptr<IRenderable>&& renderable) {
			if (nullptr != renderable) {
				renderQueue.emplace_back(std::move(renderable));
			}
		}
		void PeekToPreRender();
		void DequeueToRender();
		void Dispose();

	private:
		// 추가는 그때그때 하지만, 렌더링시 한번에 비우기 때문에 vector 사용 가능
		std::vector<std::shared_ptr<IRenderable>> renderQueue;
	};

	class RenderQueue
	{
		RenderQueue() = delete;
	public:
		// 렌더 큐에 그릴 객체를 삽입
		static void Enqueue(const std::shared_ptr<IRenderable>& renderable) { RenderQueueSingleton::Instance().Enqueue(renderable); }
		static void Enqueue(std::shared_ptr<IRenderable>&& renderable) { RenderQueueSingleton::Instance().Enqueue(renderable); }

	private:
		friend class Renderer;
		static void PeekToPreRender() { RenderQueueSingleton::Instance().PeekToPreRender(); }
		static void DequeueToRender() { RenderQueueSingleton::Instance().DequeueToRender(); }
		static void Dispose() { RenderQueueSingleton::Instance().Dispose(); }
	};
}