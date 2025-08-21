#pragma once
#include <memory>
#include "AstrumGroupObject.hpp"
#include "../Graphics/AstrumRenderTarget.hpp"
#include "../Shaders/IAstrumShaders.hpp"

class AstrumPostProcessGroupObject : public AstrumGroupObject
{
public:

private:
	std::unique_ptr<AstrumRenderTarget> renderTarget;
};