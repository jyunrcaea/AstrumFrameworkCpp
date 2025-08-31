#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "MusicBar.hpp"

namespace Selector {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject() {
			AddObjects({
				std::make_shared<MusicBar>()
			});
		}
	};
}