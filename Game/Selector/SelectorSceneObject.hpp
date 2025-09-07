#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Singletons/AstrumWindow.hpp"

namespace Selector {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject();
		virtual ~SceneObject();

	private:
		std::shared_ptr<class MusicBarListObject> musicListObject;
		std::shared_ptr<class MusicThumbnailObject> musicThumbnailObject;
	};
}