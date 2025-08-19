#pragma once
#include "DataManager.hpp"
#include "NoteGroupObject.hpp"

namespace InGame {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject() {
			AddObject(std::make_shared<NoteGroupObject>());
		}
	};
}