#pragma once
#include <functional>
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "SlideBackgroundObject.hpp"
#include "../../Astrum/Singletons/AstrumRawInput.hpp"

namespace Loading {
	class SceneObject : public AstrumGroupObject
	{
	public:
		SceneObject();
		virtual ~SceneObject();

		virtual void Update() override {
			if (AstrumRawInput::IsKeyPressed('Q'))
				slideObject->ToOpen();
			else if (AstrumRawInput::IsKeyPressed('E'))
				slideObject->ToClose();

			AstrumGroupObject::Update();
		}

		virtual void LoadScene(const std::function<void(SceneObject*)>& action) {
			slideObject->ToClose();
			slideObject->SetCloseFunction([this, action]() {
				if (action) action(this); 
				slideObject->ToOpen();
			});
		}

	private:
		std::shared_ptr<SlideBackgroundObject> slideObject = nullptr;
	};
}