#pragma once
#include "DataManager.hpp"
#include "PlayFieldObject.hpp"
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Singletons/AstrumRawInput.hpp"

namespace InGame {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject() {
			SetPositionZ(100);

			AddObject(std::make_shared<PlayFieldObject>());
		}

		virtual void Update() override {
			for (auto& key : AstrumRawInput::GetQueue()) {
				std::cout << std::format("key: {},  press: {}, time: {}\n", key.ScanCode, key.IsPressed, key.Timestamp);
			}

			AstrumGroupObject::Update();
		}
	};
}