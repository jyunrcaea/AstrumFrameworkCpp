#pragma once
#include "DataManager.hpp"
#include "../../Objects/AstrumGroupObject.hpp"
#include "PlayFieldObject.hpp"

namespace InGame {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject() {
			SetPositionZ(100);

			AddObject(std::make_shared<PlayFieldObject>());
		}
	};
}