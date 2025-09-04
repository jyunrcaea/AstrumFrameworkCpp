#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Singletons/AstrumWindow.hpp"
#include "MusicBarListObject.hpp"

namespace Selector {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject();
		virtual ~SceneObject();

	private:
		std::shared_ptr<MusicBarListObject> musicListObject;
	};
}