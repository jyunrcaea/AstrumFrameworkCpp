#pragma once
#include <string>
#include <format>
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
			for (auto& key : AstrumRawInput::GetKeyboardQueue()) {
				std::cout << std::format("key: {},  press: {}, time: {}\n", (char)key.VirtualKey, key.IsPressed, key.Timestamp);

				if (key.VirtualKey == ' ') {
					std::cout << std::format("mouse x: {}, y: {}\n", AstrumRawInput::GetMousePosition().X, AstrumRawInput::GetMousePosition().Y);
				}
			}

			AstrumGroupObject::Update();
		}
	};
}