#pragma once
#include "AstrumComponent.hpp"
#include "../Resources/AstrumTargetFont.hpp"

namespace Astrum
{
	class TextRenderComponent : public Component
	{
	public:



	private:
		std::shared_ptr<TargetFont> targetFont = nullptr;
	};
}