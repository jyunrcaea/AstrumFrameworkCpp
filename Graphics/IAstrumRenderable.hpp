#pragma once
#include <memory>
#include "../Shaders/IAstrumShaders.hpp"
#include "../Singletons/AstrumRenderer.hpp"

struct IAstrumRenderable {
    virtual ~IAstrumRenderable() = default;
    virtual void Render() = 0;

protected:
	friend class AstrumRenderer;

    // 버퍼를 업데이트하고, 다음 실제 렌더링으로 진입하는 함수.
    virtual void PreRender() = 0;
};
