#pragma once
#include "AstrumComponent.hpp"
#include "../Resources/AstrumTargetFont.hpp"

class AstrumTextRenderComponent : public AstrumComponent
{
public:



private:
	std::shared_ptr<AstrumTargetFont> targetFont = nullptr;
};