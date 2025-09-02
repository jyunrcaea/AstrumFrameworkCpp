#pragma once
#include <memory>
#include <algorithm>
#include "../../Astrum/Resources/AstrumSound.hpp"

namespace Arcaea {
	struct Music
	{
		std::make_shared<AstrumSound> previewSound;
		std::make_shared<AstrumSound> originSound;
		
	};
}