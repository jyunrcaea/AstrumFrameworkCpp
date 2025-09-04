#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "MusicBarListObject.hpp"

namespace Selector {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject() {
			SetPositionZ(100);
			AddObjects({
				std::make_shared<MusicBarListObject>()
			});
		}
	};
}