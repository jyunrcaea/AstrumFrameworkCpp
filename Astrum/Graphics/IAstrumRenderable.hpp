#pragma once
#include <memory>
#include "../Shaders/IAstrumShaders.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../Singletons/AstrumRenderQueue.hpp"

namespace Astrum {
	class RenderQueueSingleton;

	struct IRenderable : public std::enable_shared_from_this<IRenderable> {
		virtual ~IRenderable() = default;
		// 드로우 콜을 보내며 실제로 렌더링을 수행하는 함수.
		virtual void Render() = 0;

	protected:
		friend class RenderQueueSingleton;

		// 아직 드로우 콜을 보내지 않으며, 필요한 계산을 모두 수행하는 함수.
		virtual void PreRender() = 0;
	};
}
